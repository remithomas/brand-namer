let component = ReasonReact.statelessComponent("Translation");

let make = (~translation: Translation.t, _children) => {
  ...component,

  render: (_self) => {
    (
      <div className="suggestion-item">
        <div className="suggestion-item__translation">(ReasonReact.stringToElement(translation.translation))</div>
        <div className="suggestion-item__language">(ReasonReact.stringToElement(translation.language))</div>
      </div>
    );
  }
};
