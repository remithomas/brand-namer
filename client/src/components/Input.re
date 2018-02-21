type state = {
  value: string
};

type action =
  | Change(string);

let component = ReasonReact.reducerComponent("Input");

let make = (_children) => {
  ...component,

  initialState: () => {
    value: ""
  },

  reducer: action =>
    switch (action) {
    | Change(text) => (
      state => ReasonReact.Update({...state, value: text})
    )
  },

  render: ({state, send}) =>
    <div className="input">
      <input
        className="input-input"
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
