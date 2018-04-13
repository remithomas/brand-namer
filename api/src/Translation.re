type t = {
  language: string,
  translation: string
};

module Encode = {
  let encodeTranslation = (translation) => {
    open! Json.Encode;

    object_([
      ("language", string(translation.language)),
      ("translation", string(translation.translation))
    ]);
  };
  
  let encodeTranslations = (translations: array(t)) => {
    let encodedTranslations = Array.map(item => {
      encodeTranslation(item);
    }, translations);
  
    Json.Encode.jsonArray(encodedTranslations);
  };
};
