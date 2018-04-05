type action =
  | Submit
  | Change(string);

type state = {
  searchText: string,
  searchFieldRef: ref(option(Dom.element)),
};

let component = ReasonReact.reducerComponent("BrandNamerForm");

let make = (
  ~onSubmit,
  _children
) => {
  let submitHelper = state => {
    switch (String.trim(state.searchText)) {
      | "" => ReasonReact.NoUpdate
      | nonEmptyValue =>
        ReasonReact.UpdateWithSideEffects(
          {...state, searchText: nonEmptyValue},
          (_self => onSubmit(nonEmptyValue)),
        )
      };
  };

  {
    ...component,
  
    initialState: () => {
      searchText: "",
      searchFieldRef: ref(None),
    },
  
    reducer: action =>
      switch (action) {
      | Submit => submitHelper
      | Change(text) => state => ReasonReact.Update({...state, searchText: text})
      },
  
    render: ({send}) => {
      (
        <div className="form">
          <form
            className="brand-namer-form"
            onSubmit=(event => {
              ReactEventRe.Form.preventDefault(event);
              send(Submit);
            })
            noValidate=(Js.true_)
          >
            <Field
              label="Choose your possible name"
              component=(<Input onChange=((value) => send(Change(value))) />)
            />
  
            <Button type_=(Button.Submit)>
              (ReasonReact.stringToElement("Submit"))
            </Button>
          </form>
        </div>
      )
    }
  }
};
