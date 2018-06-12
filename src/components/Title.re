let component = ReasonReact.statelessComponent("Title");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className="title">
      <h1 className="title_main">(ReasonReact.string("Brand Namer"))</h1>
      <p className="title__subtitle">(ReasonReact.string("Need some inspirations..."))</p>
    </div>
};
