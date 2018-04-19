type action = 
  | Result(array(Types.Translation.t));

type state = {
  result: array(Types.Translation.t)
};

let component = ReasonReact.reducerComponent("BrandNamer");

let make = (_children) => {
  let handleSubmitFormHelper = (term, send) => {
    let apiUrlNamerTerm = Constants.apiUrlNamer ++ "/" ++ term;

    Js.Promise.(
      Axios.get(apiUrlNamerTerm)
      |> then_((response) => {
        let resultData: array(Types.Translation.t) = Types.Translation.castTranslations(response##data##translations);

        resolve(
          send(Result(resultData)) |> ignore
        );
      })
      |> catch((error) => resolve(Js.log(error)))
    );
  };

  {
    ...component,
  
    initialState: () => {
      result: [||],
    },
  
    reducer: action =>
        switch (action) {
        | Result(namesResult) => _state =>
            ReasonReact.Update({
              result: namesResult
            })
      },
  
    render: ({state, send}) => {
      let { result } = state;
  
      (
        <div className="brand-namer">
        <BrandNamerForm
          onSubmit=(value => handleSubmitFormHelper(value, send) |> ignore)
        />
  
        <BrandNamerResult
          result=result
        />
      </div>
      );
    }
  }
};
