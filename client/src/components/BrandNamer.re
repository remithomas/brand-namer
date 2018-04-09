type action = 
  | Result(array(string));

type state = {
  result: array(string)
};

let component = ReasonReact.reducerComponent("BrandNamer");

let make = (_children) => {
  let handleSubmitForm = (term) => {
    let apiUrlNamerTerm = Constants.apiUrlNamer ++ "/" ++ term;

    Js.Promise.(
      Axios.get(apiUrlNamerTerm)
      |> then_((response) => {
        let resultData: array(string) = response##data##translations;
        ReasonReact.Update(
          _state => {result: resultData}
        );

        /* ReasonReact.SideEffects(
          self => self.send(Result(response##data##translations)) |> ignore
        ); */
        resolve();
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
        | Result(namesResult) => _state => {
          ReasonReact.Update({
            result: namesResult
          });
        }
      },
  
    render: ({state}) => {
      let { result } = state;
  
      (
        <div className="brand-namer">
        <BrandNamerForm
          onSubmit=(value => handleSubmitForm(value) |> ignore)
        />
  
        <BrandNamerResult
          result=result
        />
      </div>
      );
    }
  }
};
