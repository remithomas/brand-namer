type t = {
  suggest: string,
  languages: list(string),
  hasAvailableDomain: bool,
  isCheckingDomain: bool,
  hasAvailableFacebookName: bool,
  isCheckingFacebookName: bool
};

let makeFromTranslation = (translation: Translation.t) => {
  {
    suggest: translation.translation,
    languages: [translation.language],
    hasAvailableDomain: false,
    isCheckingDomain: false,
    hasAvailableFacebookName: false,
    isCheckingFacebookName: false
  };
};
