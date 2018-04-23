Dotenv.config();

let nodeEnv = Node.Process.process##env;

let getStringEnvVariableByKey = (key) => {
  switch (Js.Dict.get(nodeEnv, key)) {
  | None => ""
  | Some(string) => string
  }
};

let getIntEnvVariableByKey = (key): int => {
  switch (Js.Dict.get(nodeEnv, key)) {
  | None => 0
  | Some(string) => int_of_string(string)
  }
};

let gcloudTranslateApiKey = getStringEnvVariableByKey("GCOULD_TRANSLATE_KEY");
let appPort: int = getIntEnvVariableByKey("APP_PORT");

let apiUrl = "http://localhost:" ++ string_of_int(appPort) ++ "/api";
let apiUrlNamer = apiUrl ++ "/namer";
let latinTranslations = [
  "en",
  "fr",
  "co", /* Corse */
];
