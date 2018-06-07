module Route53Domains = AWS_Route53Domains;
module Config = AWS_Config;

type t;

[@bs.module] external make : unit => t = "aws-sdk";
