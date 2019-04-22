type action = 
  | AddTranslation(Translation.t)
  | UpdateAvailability(string, Media.mediaType, bool)
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

let findBySuggest = (suggest, suggestions) => {
  List.find((item: Suggestion.t) => item.suggest === suggest, suggestions)
};

let replaceItemUsingSuggestTerm = (item, list, suggest) => {
  List.map((suggestion: Suggestion.t) => {
    (suggestion.suggest === suggest) ? item : suggestion;
  }, list);
};

let make = (_children) => {
  let handleSubmitFormHelper = (term, send) => {
    send(ResetSuggestions);

    SocketClient.emit(socket, Namer(term));

    /* SocketClient.on should be outside this method */
    SocketClient.on(socket, message => {
      switch message {
      | TranslationResult(translation) => send(AddTranslation(translation)) |> ignore
      | AvailabilityResult(term, mediaType, hasAvailability) => send(UpdateAvailability(term, mediaType, hasAvailability)) |> ignore
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
          /* Add language in list  */
          | item => {
            let languages = [translation.language, ...item.languages];
            let newItem = {
              ...item,
              languages: languages,
            };

            replaceItemUsingSuggestTerm(newItem, state.suggestions, translation.translation);
            /* replace item */
            /* languages */
            /* state.suggestions; */
          }
          | exception Not_found => {
              let suggestion = Suggestion.makeFromTranslation(translation);
              [suggestion, ...state.suggestions];
            }
          };

          ReasonReact.Update({
            suggestions: newSuggestionList
          })
        }
        | UpdateAvailability(term, mediaType, hasAvailability) => state => {
          let newSuggestionList = List.map((suggestion: Suggestion.t) => {
            let newSuggestion = switch mediaType {
            | Website => {
                ...suggestion,
                hasAvailableDomain: hasAvailability,
              }
            | Facebook => {
                ...suggestion,
                hasAvailableFacebookName: hasAvailability,
              }
            };

            (suggestion.suggest === term) ? newSuggestion : suggestion;
          }, state.suggestions);
          
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
