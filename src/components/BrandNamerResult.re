let component = ReasonReact.statelessComponent("BrandNamerResult");

let make = (~result: array(Translation.t), _children) => {
  ...component,

  render: (_self) => {
    Js.log(result);
    (
      <div className="brand-namer-result">
        (
          Array.mapi((index, item) => {
            <SuggestionItem key=(string_of_int(index)) translation=item />
          }, result)
            |> ReasonReact.array
        )
      </div>
    );
  }
};
