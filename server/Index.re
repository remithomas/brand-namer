open Express;

let app = express();

external castToErr : Js.Promise.error => Error.t = "%identity";

/* CORS */
App.useOnPath(app, ~path="/") @@
Middleware.from((next, _request, resource) =>
  resource
  |> Response.setHeader("Access-Control-Allow-Origin", "*")
  |> Response.setHeader("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept")
  |> next(Next.middleware)
);

App.useOnPath(
  app,
  ~path="/",
  {
    let options = Static.defaultOptions();
    Static.make("public", options) |> Static.asMiddleware;
  },
);

App.get(app, ~path="/api/namer/:term") @@
PromiseMiddleware.from(
  (next, request, resource) =>
    switch (Utils.getDictString(Request.params(request), "term")) {
      | None => Js.Promise.resolve(next(Next.route, resource))
      | Some(term) => Js.Promise.(
          Namer.asyncNamer(term)
          |> then_(
            (namings) => Namer.encodeNamingToJson(namings)
              |> (json) => resolve(Response.sendJson(json, resource))
          )
          /* |> catch((error) => Js.Promise.resolve(next(Next.error(castToErr(error), resource)))) */
        )
    }
);

let onListen = (_port, e) =>
  switch e {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1)
  | _ => Js.log @@ "Listening at " ++ Constants.appUrl
  };

App.listen(
  app,
  ~port=Constants.appPort,
  ~onListen=onListen(Constants.appPort),
  ()
);

/* RealTime Api */
module MyServer = BsSocket.Server.Make(SocketMessage);
let options = MyServer.makeOptions(());
let io = MyServer.createWithPort(Constants.socketPort, options);

MyServer.onConnect(
  io,
  socket => {
    open MyServer;
    print_endline("Got a connection!");

    Socket.on(
      socket,
      fun
      | Namer(term) => {
        Js.log("namer...");
        Js.log(term);
        let translationItem: Translation.t = {
          language: "fr",
          translation: term,
        };
        Socket.emit(socket, TranslationResult(translationItem));
      }
      | Hi => Js.log("oh, hi client.")
    );
  }
);
