let component = ReasonReact.statelessComponent("SuggestionItem");

let make = (~translation: Translation.t, _children) => {
  ...component,

  render: (_self) => {
    (
      <div className="suggestion-item">
        <div className="suggestion-item__translation">(ReasonReact.string(translation.translation))</div>
        <div className="suggestion-item__languages">(ReasonReact.string(translation.language))</div>

        <div className="suggestion-item__media">
          (ReasonReact.string("ok example.com"))
          (ReasonReact.string("ok facebook.com/example"))
        </div>
      </div>
    );
  }
};
