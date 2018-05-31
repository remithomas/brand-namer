open GCloud;

type naming = {
  term: string,
  synonymes: array(string),
  translations: array(Translation.t),
  suggestions: array(string)
};

exception NamerError(string);
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

let arrayFromList = (~init: 'a, l: list('a)) => {
  let arr = ArrayLabels.make(ListLabels.length(l), init);
  ListLabels.iteri(~f=(i, x) => arr[i]=x, l);
  arr;
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
    |> catch((error) => {
      Js.log(error);
      reject(TranslationError("Translating error"))
    })
  );
};

let makeTranslationListFromPromises = (latinTranslationPromiseResults) => {
  Array.mapi((index, result) => {
    let translation: Translation.t = {
      language: List.nth(Constants.latinTranslations, index),
      translation: result
    };
    translation;
  }, latinTranslationPromiseResults);
};

let asyncNamer = (term: string) => {
  let latinTranslations = List.map(languageItem => translateTerm(term, languageItem), Constants.latinTranslations);

  Js.Promise.(
    all(Array.of_list(latinTranslations))
    |> then_(
      latinTranslationPromiseResults => {
        let translations = makeTranslationListFromPromises(latinTranslationPromiseResults);

        resolve(namer(
          ~term=term,
          ~synonymes= [||],
          ~translations=translations,
          ~suggestions= [||]
        ));
      }
    )
  );
};

let translate = (term) => {
  /* return Promise.resolve */
  Js.Promise.resolve(term);
  /* Js.Promise.(
    Js.Promise.resolve(term)
    |> then_((translation) => resolve(translation))
    |> catch((_error) => reject(NamerError("Something happens")))
  ); */
};

let checkFacebookAvaibility = (facebookName) => {
  let url = "https://graph.facebook.com/v3.0/" ++ facebookName ++ "?access_token=" ++ Constants.facebookAuthTocken;

  Js.Promise.(
    Axios.get(url)
    |> then_((_response) => resolve(false))
    |> catch((_error) => resolve(true))
  );
};

let checkDomainAvaibility = (domainName) => {
  /* return Promise.resolve */
  Js.Promise.resolve(true);
};

let askTranslationPromises = (term) => {
  /* List.map(languageItem => (languageItem, translateTerm(term, languageItem)), Constants.latinTranslations); */
  /* Mockup */
  List.map(languageItem => {
    (languageItem, Js.Promise.resolve(term ++ "_" ++ languageItem));
  }, Constants.latinTranslations);
};
