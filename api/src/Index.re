open Express;

let app = express();

external castToErr : Js.Promise.error => Error.t = "%identity";

App.get(app, ~path="/") @@
Middleware.from(
  (_next, _request) => Response.sendJson(Utils.makeSuccessJson())
);

App.get(app, ~path="/api/namer/:term") @@
PromiseMiddleware.from(
  (next, request, resource) =>
    switch (Utils.getDictString(Request.params(request), "term")) {
      | None => Js.Promise.resolve(next(Next.route, resource))
      | Some(term) => Js.Promise.(
          Namer.asyncNamer(term, "en")
          |> then_(
            (namings) => Namer.encodeNamingToJson(namings)
              |> (json) => resolve(Response.sendJson(json, resource))
          )
          /* |> catch((error) => Js.Promise.resolve(next(Next.error(castToErr(error), resource)))) */
        )
    }
);

let onListen = (port, e) =>
  switch e {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1)
  | _ => Js.log @@ "Listening at http://127.0.0.1:" ++ string_of_int(port)
  };

App.listen(
  app,
  ~port=Constants.appPort,
  ~onListen=onListen(Constants.appPort),
  ()
);
