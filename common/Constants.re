Dotenv.config();

let nodeEnv = Node.Process.process##env;

let getStringEnvVariableByKey = (key) => {
  switch (Js.Dict.get(nodeEnv, key)) {
  | None => ""
  | Some(string) => string
  }
};

let getIntEnvVariableByKey = (key, default): int => {
  switch (Js.Dict.get(nodeEnv, key)) {
  | None => default
  | Some(string) => int_of_string(string)
  }
};

let gcloudTranslateApiKey = getStringEnvVariableByKey("GCOULD_TRANSLATE_KEY");
let appPort: int = getIntEnvVariableByKey("APP_PORT", 3000);
let socketPort: int = getIntEnvVariableByKey("SOCKET_PORT", 3001);

let socketUrl = "http://localhost:" ++ string_of_int(socketPort);
let appUrl = "http://localhost:" ++ string_of_int(appPort);
let apiUrl = appUrl ++ "/api";
let apiUrlNamer = apiUrl ++ "/namer";
let latinTranslations = [
  "en",
  "fr",
  "co", /* Corse */
];
