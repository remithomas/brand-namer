let component = ReasonReact.statelessComponent("BrandNamer");

let handleSubmitForm = (value) => {
  Js.log("submit !!");
  Js.log(value);
};

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className="brand-namer">
      <BrandNamerForm
        onSubmit=(value => handleSubmitForm(value))
      />
    </div>
};
