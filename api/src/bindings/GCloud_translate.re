/* type config = Js.t({.});

[@bs.obj]
external makeClientConfig : (
  ~projectId: string
) => config = ""; */

type clientConfig = {
  .
  /* "projectId": string, */
  "key": string,
};

type t;

/* type translateResponse('a) = {
  .
  "translations": 'a
}; */

/* type translations =
  | String(string)
  | List(array(string));

type translateResponse = list(translations); */

type translateResponse = array(string);

/* [@bs.module] [@bs.new] external make : unit => t = "@google-cloud/translate"; */
[@bs.module] [@bs.new] external make : clientConfig => t = "@google-cloud/translate";

[@bs.send] external translate : (t, string, string) => Js.Promise.t(translateResponse) = "translate";

/* // Imports the Google Cloud client library
const Translate = require('@google-cloud/translate');

// Your Google Cloud Platform project ID
const projectId = 'YOUR_PROJECT_ID';

// Instantiates a client
const translate = new Translate({
  projectId: projectId,
});

// The text to translate
const text = 'Hello, world!';
// The target language
const target = 'ru';

// Translates some text into Russian
translate
  .translate(text, target)
  .then(results => {
    const translation = results[0];

    console.log(`Text: ${text}`);
    console.log(`Translation: ${translation}`);
  })
  .catch(err => {
    console.error('ERROR:', err);
  }); */
