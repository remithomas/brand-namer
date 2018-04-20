let component = ReasonReact.statelessComponent("BrandNamerResult");

let make = (~result: array(Translation.t), _children) => {
  ...component,

  render: (_self) => {
    Js.log(result);
    (
      <div className="brand-namer-result">
        (
          Array.mapi((index, item) => {
            
            /* let tr = item; */
            <SuggestionItem key=(string_of_int(index)) translation=item />
            /* <div /> */
          }, result)
            /* |> List.toArray */
            |> ReasonReact.arrayToElement
        )
      </div>
    );
  }
};
