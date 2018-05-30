type t = {
  suggest: string,
  languages: list(string),
  hasAvailableDomain: bool,
  hasAvailableFacebookName: bool,
};

let makeFromTranslation = (translation: Translation.t) => {
  {
    suggest: translation.translation,
    languages: [translation.language],
    hasAvailableDomain: false,
    hasAvailableFacebookName: false,
  };
};
