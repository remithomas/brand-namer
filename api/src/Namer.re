open GCloud;

type naming = {
  term: string,
  translations: array(string)
};

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
    /* "projectId": "brand-namer-1522951086893", */
    "key": "AIzaSyASAnHi5hJuApvaoxTOf1yPxaQ4PfiSIHA"
  };

  let translater = Translate.make(config);

  Js.Promise.(
    Translate.translate(translater, term, language)
    |> then_((response) => resolve(response[0]))
    /* |> catch((error) => reject(error)) */
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
