let component = ReasonReact.statelessComponent("BrandNamerApp");

let make = (children) => {
  ...component,
  render: (self) =>
    <div className="app">
      <div className="title"> (ReasonReact.stringToElement("Brand namer")) </div>
    </div>
};
