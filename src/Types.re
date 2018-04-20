/* module Translation = {
  type t = {
    language: string,
    translation: string
  };

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

  let castTranslations = arrayOfObject => 
    Array.map(obj => castTranslation(obj), arrayOfObject);
}; */
