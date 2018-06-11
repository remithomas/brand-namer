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

App.get(app, ~path="/api/facebook/:term") @@
PromiseMiddleware.from(
  (next, request, resource) =>
    switch (Utils.getDictString(Request.params(request), "term")) {
      | None => Js.Promise.resolve(next(Next.route, resource))
      | Some(term) => Js.Promise.(
        Namer.checkFacebookAvailability(term)
        |> then_((success) => {
          let json = Utils.makeSuccessJson(success);
          resolve(Response.sendJson(json, resource));
        })
        /* |> catch((error) => reject(exception(error))) */
      )
    }
);

App.get(app, ~path="/api/domain/:term") @@
PromiseMiddleware.from(
  (next, request, resource) =>
    switch (Utils.getDictString(Request.params(request), "term")) {
      | None => Js.Promise.resolve(next(Next.route, resource))
      | Some(term) => Js.Promise.(
        Namer.checkDotComDomainAvailability(term)
        |> then_((success) => {
          let json = Utils.makeSuccessJson(success);
          resolve(Response.sendJson(json, resource));
        })
      )
    }
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

/* App State */
/* TODO: persist result in state to reduce number of requests */
let suggestions = [];

/* RealTime Api */
module MyServer = BsSocket.Server.Make(SocketMessage);
let options = MyServer.makeOptions(());
let io = MyServer.createWithPort(Constants.socketPort, options);

let sendTranslationToSocket = (translation, language, socket) => {
  open MyServer;

  let translationItem = Translation.make(language, translation);
  Socket.emit(socket, TranslationResult(translationItem));
  Js.Promise.resolve(translation);
};

let sendFacebookAvailabilityFromTranslationToSocket = (translation, socket) => {
  open MyServer;

  Js.Promise.(
    Namer.checkFacebookAvailability(translation)
    |> then_((hasAvailability) => {
      Socket.emit(socket, AvailabilityResult(translation, Media.Facebook, hasAvailability));
      resolve(translation);
    })
  );
};

let sendWebsiteAvailabilityFromTranslationToSocket = (translation, socket) => {
  open MyServer;

  Js.Promise.(
    Namer.checkDotComDomainAvailability(translation)
    |> then_((hasAvailability) => {
      Socket.emit(socket, AvailabilityResult(translation, Media.Website, hasAvailability));
      resolve(translation);
    })
  );
};

MyServer.onConnect(
  io,
  socket => {
    open MyServer;
    print_endline("Got a connection!");

    Socket.on(
      socket,
      fun
      | Namer(term) => {
        let translationPromises = Namer.askTranslationPromises(term);

        List.iter(((language, translationPromise)) => {
          Js.Promise.(
            translationPromise
            |> then_((translation) => sendTranslationToSocket(translation, language, socket))
            |> then_((translation) => sendFacebookAvailabilityFromTranslationToSocket(translation, socket))
            |> then_((translation) => sendWebsiteAvailabilityFromTranslationToSocket(translation, socket))
            |> ignore
          )
        }, translationPromises);
      }
      | Hi => Js.log("oh, hi client.")
    );
  }
);
