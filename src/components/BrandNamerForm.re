type action =
  | Submit
  | Change(string);

type state = {
  searchText: string,
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
          {searchText: nonEmptyValue},
          (_self => onSubmit(nonEmptyValue)),
        )
      };
  };

  {
    ...component,
  
    initialState: () => {
      searchText: "",
    },
  
    reducer: action =>
      switch (action) {
      | Submit => submitHelper
      | Change(text) => _state => ReasonReact.Update({searchText: text})
      },
  
    render: ({send}) => {
      (
        <form
          className="brand-namer-form"
          onSubmit=(event => {
            ReactEventRe.Form.preventDefault(event);
            send(Submit);
          })
          noValidate=(true)
        >
          <Field
            label=""
            className="brand-namer-form__field"
            component=(<Input placeholder="Choose your possible name" className="brand-namer-form__input" onChange=(value => send(Change(value))) />)
          />

          <Button type_=(Button.Submit) className="brand-namer-form__submit-button">
            (ReasonReact.string("Submit"))
          </Button>
        </form>
      )
    }
  }
};
