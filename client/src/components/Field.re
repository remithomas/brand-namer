let componentField = ReasonReact.statelessComponent("Field");

let make = (
  ~label: string = "", ~component: ReasonReact.reactElement, _children) => {
  ...componentField,

  render: (_self) =>
    <div className="brand-namer">
      <label>
        (ReasonReact.stringToElement(label))
        {component}
      </label>
    </div>
};
