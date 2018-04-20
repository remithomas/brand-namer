let component = ReasonReact.statelessComponent("Title");

let make = (~title, _children) => {
  ...component,
  render: (_self) =>
    <div className="title">
      (ReasonReact.stringToElement(title))
    </div>
};
