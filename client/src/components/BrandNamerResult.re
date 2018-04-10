let component = ReasonReact.statelessComponent("BrandNamerResult");

let make = (~result: array(string), _children) => {
  ...component,

  render: (_self) => {
    (
      <div className="brand-namer-result">
        (
          Array.map(translation => <Translation key=translation translation=translation />, result)
            |> ReasonReact.arrayToElement
        )
      </div>
    );
  }
};
