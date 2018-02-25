open Express;

let appPort = 3001;

let app = express();

App.get(app, ~path="/") @@
Middleware.from(
  (_next, _request) => Response.sendJson(Utils.makeSuccessJson())
);

App.get(app, ~path="/api/namer/:term") @@
Middleware.from(
  (next, request, resource) =>
    switch (Utils.getDictString(Request.params(request), "term")) {
      | None => next(Next.route, resource)
      | Some(term) => Namer.namer(term)
        |> (namings) => Namer.encodeNamingToJson(namings)
        |> (json) => Response.sendJson(json, resource)
    }
);

let onListen = (port, e) =>
  switch e {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1)
  | _ => Js.log @@ "Listening at http://127.0.0.1:" ++ string_of_int(port)
  };

App.listen(app, ~port=appPort, ~onListen=onListen(appPort), ());
