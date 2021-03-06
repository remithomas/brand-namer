let component = ReasonReact.statelessComponent("BrandNamerApp");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className="brand-namer-app">
      <div className="brand-namer-app__container">
        <Title />
        <BrandNamer />
      </div>
    </div>
};
