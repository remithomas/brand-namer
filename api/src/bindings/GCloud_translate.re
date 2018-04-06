type clientConfig = {
  .
  "key": string,
};

type t;

type translateResponse = array(string);

[@bs.module] [@bs.new] external make : clientConfig => t = "@google-cloud/translate";

[@bs.send] external translate : (t, string, string) => Js.Promise.t(translateResponse) = "translate";
