let component = ReasonReact.statelessComponent("MediaItem");

let make = (
  ~isAvailable: bool,
  ~mediaName: string,
  ~mediaType: string,
  _children
) => {
  ...component,

  render: (_self) => {
    (
      <div className="media-item">
        <div className="media-item__is-available">(ReasonReact.string("isAvailable"))</div>
        <div className="media-item__media-type">(ReasonReact.string(mediaType))</div>
        <div className="media-item__media-name">(ReasonReact.string(mediaName))</div>
      </div>
    );
  }
};
