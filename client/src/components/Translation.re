let component = ReasonReact.statelessComponent("Translation");

let make = (~translation: Types.Translation.t, _children) => {
  ...component,

  render: (_self) => {
    (
      <div className="translation">
        <div className="translation__translation">(ReasonReact.stringToElement(translation.translation))</div>
        <div className="translation__language">(ReasonReact.stringToElement(translation.language))</div>
      </div>
    );
  }
};
