let component = ReasonReact.statelessComponent("MediaItem");

let make = (
  ~isAvailable: bool,
  ~mediaName: string,
  ~mediaType: Media.mediaType,
  _children
) => {
  ...component,

  render: (_self) => {
    (
      <div className="media-item">
        <div className="media-item__is-available">(
          switch isAvailable {
          | true => "Available"
          | false => "Not available"
          } |> ReasonReact.string
        )</div>

        <div className="media-item__media-type">(
          switch mediaType {
          | Facebook => "Facebook"
          | Website => "Website"
          } |> ReasonReact.string
        )</div>

        <div className="media-item__media-name">(ReasonReact.string(mediaName))</div>
      </div>
    );
  }
};
