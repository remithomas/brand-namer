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
    open ReBemHelper;

    let classes = bem(
      ~block="media-item",
      ~modifiers=[
        String(mediaType |> Media.encodeMediaType),
        Boolean("available", isAvailable)
      ],
      ()
    );

    (
      <div className=classes>
        (
          switch mediaType {
          | Media.Facebook => <img src=facebookIcon alt=mediaName />
          | Media.Website => <img src=webIcon alt=mediaName />
          }
        )
      </div>
    );
  }
};
