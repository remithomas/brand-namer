let component = ReasonReact.statelessComponent("BrandNamerForm");

let make = (_children) => {
  ...component,
  render: (_self) => {
    (
      <div className="form">
        <form>
          <Field
            label="Choose your possible name"
            component=(<Input />)
          />

          <Button type_=Submit>
            (ReasonReact.stringToElement("Submit"))
          </Button>
        </form>
      </div>
    )
  }
};
