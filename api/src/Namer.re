type naming = {
  term: string
};

let namer = (term: string) => {
  {
    term: term
  }
};

let encodeNamingToJson = (namings) => {
  /* Json.Encode.parseOrRaise(namings); */
  Json.Encode.(
    object_([
      ("term", string(namings.term))
    ])
  )
};
