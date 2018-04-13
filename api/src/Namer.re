open GCloud;

type naming = {
  term: string,
  synonymes: array(string),
  translations: array(Translation.t),
  suggestions: array(string)
};

exception TranslationError(string);

let namer = (
  ~term: string,
  ~synonymes: array(string),
  ~translations: array(Translation.t),
  ~suggestions: array(string)
) => {
  {
    term,
    synonymes,
    translations,
    suggestions
  }
};

let encodeNamingToJson = (namingData) => {
  Json.Encode.(
    object_([
      ("term", string(namingData.term)),
      ("synonymes", Json.Encode.stringArray(namingData.synonymes)),
      ("translations", Translation.Encode.encodeTranslations(namingData.translations)),
      ("suggestions", Json.Encode.stringArray(namingData.suggestions))
    ])
  )
};

let translateTerm = (term: string, language: string) => {
  let config = {
    "key": Constants.gcloudTranslateApiKey
  };

  let translater = Translate.make(config);

  Js.Promise.(
    Translate.translate(translater, term, language)
    |> then_((response) => resolve(response[0]))
    /* |> catch((error) => reject(TranslationError(error))) */
  );
};

let asyncNamer = (term: string, language: string) => {
  Js.Promise.(
    translateTerm(term, language)
    |> then_(
      (translations) => {
        let translation: Translation.t = {
          language: language,
          translation: translations
        };
        resolve(namer(
          ~term=term,
          ~synonymes= [||],
          ~translations=[|translation|],
          ~suggestions= [||]
        ))
      }
    )
    /* |> catch((error) => resolve(Js.log(error))) */
  );
};
