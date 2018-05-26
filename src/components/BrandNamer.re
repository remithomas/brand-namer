type action = 
  | AddTranslation(Translation.t)
  | Result(array(Translation.t));

type state = {
  result: array(Translation.t),
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
      result: [||],
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
        | Result(namesResult) => state =>
            ReasonReact.Update({
              ...state,
              result: namesResult
            })
      },
  
    render: ({state, send}) => {
      let { translations } = state;
  
      (
        <div className="brand-namer">
        <BrandNamerForm
          onSubmit=(value => handleSubmitFormHelper(value, send) |> ignore)
        />
  
        <BrandNamerResult
          result=Array.of_list(translations)
        />
      </div>
      );
    }
  }
};
