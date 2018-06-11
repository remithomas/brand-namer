open ReBemHelper;

let facebookIcon = [%bs.raw {|require('../../../../src/assets/facebook.svg')|}];
let webIcon = [%bs.raw {|require('../../../../src/assets/web.svg')|}];

let component = ReasonReact.statelessComponent("MediaItem");

let make = (
  ~isAvailable: bool,
  ~mediaName: string,
  ~mediaType: Media.mediaType,
  _children
) => {
  ...component,

  render: (_self) => {
    let classes = bem(
      ~block="media-item",
      ~modifiers=[
        String(mediaName),
        Boolean("available", isAvailable)
      ],
      ()
    );

    (
      <div className=classes>
        <div className="media-item__is-available">(
          switch mediaType {
          | Media.Facebook => <img src=facebookIcon />
          | Media.Website => <img src=webIcon />
          }
        )</div>
        
        <div className="media-item__is-available">(
          switch isAvailable {
          | true => "ok"
          | false => "no"
          } |> ReasonReact.string
        )</div>

        <div className="media-item__media-name">(ReasonReact.string(mediaName))</div>
      </div>
    );
  }
};
