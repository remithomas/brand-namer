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
  let translater = Translate.createTranslate();

  Js.Promise.(
    Translate.translate(translater, "à traduire")
    |> then_((response) => resolve(Js.log(response##translations)))
    |> catch((error) => resolve(Js.log(error)))
  );
};
