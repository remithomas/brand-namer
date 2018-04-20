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

module Decode = {
  let decodeTranslation = json =>
    Json.Decode.{
      language: json |> field("language", string),
      translation: json |> field("translation", string)
    };

  let decodeTranslations = json => Json.Decode.(dict(decodeTranslation, json));

  let castTranslation = js_json => {
      language: js_json##language,
      translation: js_json##translation
    };

  let castTranslations = arrayOfObject => Array.map(obj => castTranslation(obj), arrayOfObject);
}
