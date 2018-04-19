open ReBemHelper;

type state = {
  value: string,
  valueFieldRef: ref(option(Dom.element)),
};

type action =
  | Change(string);

let setValueFieldRef = (r, {ReasonReact.state}) =>
  state.valueFieldRef := Js.Nullable.toOption(r);

let component = ReasonReact.reducerComponent("Input");

let make = (
  ~onChange,
  _children
) => {
  ...component,

  initialState: () => {
    value: "",
    valueFieldRef: ref(None),
  },

  reducer: action =>
    switch (action) {
    | Change(text) =>
      (state) => 
        ReasonReact.UpdateWithSideEffects(
          {...state, value: text},
          (_self => onChange(text)),
        );
  },

  render: ({state, handle, send}) =>
    <div className="input">
      <input
        ref=(handle(setValueFieldRef))
        className=(bem(~block="input", ~element="input", ()))
        value=state.value
        onChange=(
          event =>
            send(
              Change(
                ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value
              )
            )
        )
      />
    </div>
};
