open GCloud;

type naming = {
  term: string,
  translations: array(string)
};

exception TranslationError(string);

let namer = (term: string, translations: array(string)) => {
  {
    term,
    translations,
  }
};

let encodeNamingToJson = (namingData) => {
  Json.Encode.(
    object_([
      ("term", string(namingData.term)),
      ("translations", Json.Encode.stringArray(namingData.translations))
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
      (translations) => resolve(namer(term, [|translations|]))
    )
    /* |> catch((error) => resolve(Js.log(error))) */
  );
};
