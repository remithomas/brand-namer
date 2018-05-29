type action = 
  | AddTranslation(Translation.t)
  | UpdateSuggestion(Suggestion.t)
  | ResetSuggestions;

type state = {
  suggestions: list(Suggestion.t)
};

let component = ReasonReact.reducerComponent("BrandNamer");

module SocketClient = BsSocket.Client.Make(SocketMessage);
let socket = SocketClient.createWithUrl(Constants.socketUrl);

let findByTranslation = (translation: Translation.t, suggestions) => {
  List.find((item: Suggestion.t) => item.suggest === translation.translation, suggestions)
};

let make = (_children) => {
  let handleSubmitFormHelper = (term, send) => {
    send(ResetSuggestions);

    SocketClient.emit(socket, Namer(term));

    /* SocketClient.on should be outside this method */
    SocketClient.on(socket, message => {
      switch message {
      | TranslationResult(translation) => send(AddTranslation(translation)) |> ignore
      };
    });
  };

  {
    ...component,
  
    initialState: () => {
      suggestions: []
    },
  
    reducer: action =>
        switch (action) {
        | AddTranslation(translation) => state => {
          let newSuggestionList = switch(findByTranslation(translation, state.suggestions)) {
          | _item => state.suggestions
          | exception Not_found => {
            let suggestion = Suggestion.makeFromTranslation(translation);
            [suggestion, ...state.suggestions];
          }
          };

          ReasonReact.Update({
            suggestions: newSuggestionList
          })
        }
        | UpdateSuggestion(_suggestion) => _state => ReasonReact.NoUpdate
        | ResetSuggestions => _state => {
          ReasonReact.Update({
            suggestions: []
          })
        }
      },
  
    render: ({state, send}) => {
      let { suggestions } = state;

      (
        <div className="brand-namer">
        <BrandNamerForm
          onSubmit=(value => {
            handleSubmitFormHelper(value, send) |> ignore
          })
        />

        <SuggestionsList
          suggestions=suggestions
        />
      </div>
      );
    }
  }
};
