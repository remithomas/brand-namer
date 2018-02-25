/* make a common JSON object representing success */
let makeSuccessJson = () => {
  let json = Js.Dict.empty();
  Js.Dict.set(json, "success", Js.Json.boolean(Js.true_));
  Js.Json.object_(json)
};

/* return the string value for [key], None if the key is not in [dict]
   TODO once BOption.map is released */
let getDictString = (dict, key) =>
  switch (Js.Dict.get(dict, key)) {
  | Some(json) => Js.Json.decodeString(json)
  | _ => None
};
