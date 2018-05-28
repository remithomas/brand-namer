let component = ReasonReact.statelessComponent("SuggestionsList");

let make = (~suggestions: list(Suggestion.t), _children) => {
  ...component,

  render: (_self) => {
    (
      <div className="brand-namer-suggestions__list">
        (
          List.mapi((index, suggestion) => {
            <SuggestionItem suggestion=suggestion key=(string_of_int(index)) />;
          }, suggestions)
          |> Array.of_list
          |> ReasonReact.array
        )
      </div>
    );
  }
};
