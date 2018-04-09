let component = ReasonReact.statelessComponent("BrandNamerResult");

let make = (~result: array(string), _children) => {
  ...component,

  render: (_self) => {
    Js.log(result);

    (
      <div className="brand-namer-result">
        (ReasonReact.stringToElement("result"))
      </div>
    );
  }
};
