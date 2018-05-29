let component = ReasonReact.statelessComponent("SuggestionItem");

let make = (~suggestion: Suggestion.t, _children) => {
  ...component,

  render: (_self) => {
    (
      <div className="suggestion-item">
        <div className="suggestion-item__translation">(ReasonReact.string(suggestion.suggest))</div>
        <div className="suggestion-item__languages">(String.concat(", ", suggestion.languages) |> ReasonReact.string)</div>

        <div className="suggestion-item__media">
          <MediaItem
            mediaType=Media.Facebook
            mediaName=("facebook/" ++ suggestion.suggest)
            isAvailable=suggestion.hasAvailableFacebookName
          />
          <MediaItem
            mediaType=Media.Website
            mediaName=(suggestion.suggest ++ ".com")
            isAvailable=suggestion.hasAvailableDomain
          />
        </div>
      </div>
    );
  }
};
