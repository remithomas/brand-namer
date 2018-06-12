let component = ReasonReact.statelessComponent("SuggestionItem");

let make = (~suggestion: Suggestion.t, _children) => {
  ...component,

  render: (_self) => {
    open ReBemHelper;

    let itemCssClasses = bem(
      ~block="suggestion-item",
      ~modifiers=[
        Boolean("available", suggestion.hasAvailableFacebookName && suggestion.hasAvailableDomain)
      ],
      ()
    );

    (
      <div className=itemCssClasses>
        <div className="suggestion-item__translation">(ReasonReact.string(suggestion.suggest))</div>
        <div className="suggestion-item__languages">(String.concat(", ", suggestion.languages) |> ReasonReact.string)</div>

        <div className="suggestion-item__media">
          <MediaItem
            mediaType=Media.Facebook
            mediaName=(Media.formatFacebookName(suggestion.suggest))
            isAvailable=suggestion.hasAvailableFacebookName
          />
          <MediaItem
            mediaType=Media.Website
            mediaName=(Media.formatDomainName(suggestion.suggest))
            isAvailable=suggestion.hasAvailableDomain
          />
        </div>
      </div>
    );
  }
};
