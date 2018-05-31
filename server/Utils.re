/* make a common JSON object representing success */
let makeSuccessJson = (success) => {
  let json = Js.Dict.empty();
  Js.Dict.set(json, "success", Js.Json.boolean(success));
  Js.Json.object_(json)
};

let getDictString = (dict, key) =>
  switch (Js.Dict.get(dict, key)) {
  | Some(json) => Js.Json.decodeString(json)
  | _ => None
};
