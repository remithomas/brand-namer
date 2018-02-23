open Express;

let appPort = 3001; 

/* make a common JSON object representing success */
let makeSuccessJson = () => {
  let json = Js.Dict.empty();
  Js.Dict.set(json, "success", Js.Json.boolean(Js.true_));
  Js.Json.object_(json)
};

let app = express();

App.get(app, ~path="/") @@
Middleware.from(
  (_next, _req) => Response.sendJson(makeSuccessJson())
);

let onListen = (port, e) =>
  switch e {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1)
  | _ => Js.log @@ "Listening at http://127.0.0.1:" ++ string_of_int(port)
  };

App.listen(app,  ~port=appPort, ~onListen=onListen(appPort), ());
