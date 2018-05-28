type action = 
  | AddTranslation(Translation.t)
  | UpdateSuggestion(Suggestion.t);

type state = {
  suggestions: list(Suggestion.t),
  translations: list(Translation.t)
};

let component = ReasonReact.reducerComponent("BrandNamer");

module SocketClient = BsSocket.Client.Make(SocketMessage);
let socket = SocketClient.createWithUrl(Constants.socketUrl);

let make = (_children) => {
  let handleSubmitFormHelper = (term, send) => {
    SocketClient.emit(socket, Namer(term));

    SocketClient.on(socket, message => {
      switch message {
      | TranslationResult(translation) => send(AddTranslation(translation)) |> ignore
      };
    });
  };

  {
    ...component,
  
    initialState: () => {
      suggestions: [{
        suggest: "string",
        languages: ["fr"],
        hasAvailableDomain: true,
        isCheckingDomain: false,
        hasAvailableFacebookName: true,
        isCheckingFacebookName: false
      }],
      translations: [],
    },
  
    reducer: action =>
        switch (action) {
        | AddTranslation(translation) => state => {
          let newTranslationList = [translation, ...state.translations];
          ReasonReact.Update({
            ...state,
            translations: newTranslationList
          })
        }
        | UpdateSuggestion(_suggestion) => _state => ReasonReact.NoUpdate
      },
  
    render: ({state, send}) => {
      let { suggestions } = state;
  
      (
        <div className="brand-namer">
        <BrandNamerForm
          onSubmit=(value => handleSubmitFormHelper(value, send) |> ignore)
        />

        <SuggestionsList
          suggestions=suggestions
        />
      </div>
      );
    }
  }
};
