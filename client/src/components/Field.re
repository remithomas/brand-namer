let componentField = ReasonReact.statelessComponent("Field");

let make = (
  ~label: string = "", ~component: ReasonReact.reactElement, _children) => {
  ...componentField,

  render: (_self) =>
    <div className="field">
      <label>
        (ReasonReact.stringToElement(label))
        {component}
      </label>
    </div>
};
