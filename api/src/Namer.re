open GCloud;

type naming = {
  term: string
};

let namer = (term: string) => {
  {
    term: term
  }
};

let encodeNamingToJson = (namings) => {
  Json.Encode.(
    object_([
      ("term", string(namings.term))
    ])
  )
};

let translateTerm = (term: string, language: string) => {
  let config = {
    "projectId": "aaaa-bbbb-cccc-dddd"
  };

  let translater = Translate.make(config);

  Js.log(term ++ " " ++ language);
  /* Translate.translate(translater, "à traduire", "en") */
  /* translater |> Translate.translate("à traduire", "en") */

  Js.Promise.(
    Translate.translate(translater, "à traduire", "en")
    |> then_((response) => resolve(Js.log(response##translations)))
    |> catch((error) => resolve(Js.log(error)))
  );
};
