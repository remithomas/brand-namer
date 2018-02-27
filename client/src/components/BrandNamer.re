let component = ReasonReact.statelessComponent("BrandNamer");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className="brand-namer">
      <BrandNamerForm />
    </div>
};
