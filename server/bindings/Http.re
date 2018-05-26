type t;

[@bs.module "http"] external create : Express.App.t => t = "createServer";
[@bs.send] external listen : (t, int, unit => unit) => unit = "";
