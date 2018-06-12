let componentField = ReasonReact.statelessComponent("Field");

let make = (
  ~label: string = "",
  ~component: ReasonReact.reactElement,
  ~className =  "",
  _children
) => {
  ...componentField,

  render: (_self) =>
    <div className=("field " ++ className)>
      <label>
        (ReasonReact.string(label))
        {component}
      </label>
    </div>
};
