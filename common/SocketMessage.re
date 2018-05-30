type dataT =
  | Data(string)
  | OrOthers;

  type data2T = string;

type clientToServer =
  /* | Shared(shared) */
  | Namer(string)
  | Hi;

/* In this simple example, the server has no unique messages, unlike
  the client, which is polite and says hi after connecting (in addition
  to sending all the shared message types). */
type serverToClient = 
  | TranslationResult(Translation.t)
  | AvailabilityResult(string, Media.mediaType, bool);
