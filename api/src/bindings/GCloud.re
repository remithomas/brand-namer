type clientConfig = {
  .
  "projectId": string,
};

module Translate = {
  type t;

  type translateResponse('a) = {
    .
    "translations": 'a
  };
  /* [@bs.module] external make : unit => t = "@google-cloud/translate"; */

  [@bs.module "@google-cloud/translate"] [@bs.new] external createTranslate : unit => t = "Translate";
  /* [@bs.send] external translate : (t, string) => unit = ""; */
  [@bs.send] external translate : (t, string) => Js.Promise.t(translateResponse('a)) = "";
};


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
