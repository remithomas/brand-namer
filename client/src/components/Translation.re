let component = ReasonReact.statelessComponent("Translation");

let make = (~translation, _children) => {
  ...component,

  render: (_self) => {
    (
      <div className="translation">
        (ReasonReact.stringToElement(translation))
      </div>
    );
  }
};
