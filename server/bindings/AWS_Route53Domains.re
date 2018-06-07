type t;

type availability = 
  | Available
  | AvailableReserved
  | AvailablePreorder
  | Pending
  | UnAvailable
  | UnAvailablePremium
  | UnAvailableRestricted
  | Reserved
  | DontKnow;

type error = 
  | InvalidInput 
  | UnsupportedTLD;

[@bs.deriving abstract]
type params = {
  [@bs.as "DomainName"] domainName: string,
  [@bs.as "IdnLangCode"] [@bs.optional] idnLangCode: string
};

[@bs.deriving abstract]
type response = {
  [@bs.as "Availability"] availability: string
};

type callback = ((Js.Nullable.t(exn), Js.Nullable.t(response)) => unit);

exception Route53DomainsError(string);

let decodeResult = availabilityResult => switch availabilityResult {
  | "AVAILABLE" => Available
  | "AVAILABLE_RESERVED" => AvailableReserved
  | "AVAILABLE_PREORDER" => AvailablePreorder
  | "PENDING" => Pending
  | "UNAVAILABLE" => UnAvailable
  | "UNAVAILABLE_PREMIUM" => UnAvailablePremium
  | "UNAVAILABLE_RESTRICTED" => UnAvailableRestricted
  | "RESERVED" => Reserved
  | "DONT_KNOW" => DontKnow;
  | _ => DontKnow;
  };
  
[@bs.module "aws-sdk"] [@bs.new] external make : unit => t = "Route53Domains";
[@bs.module "aws-sdk"] [@bs.new] external makeWithConfig : AWS_Config.config => t = "Route53Domains";

[@bs.send] external _checkDomainAvailability: (t, params, callback) => Js.Promise.t(availability) = "checkDomainAvailability";

let checkDomainAvailability = (service: t, domainName: string) => {
  Js.Promise.make((~resolve, ~reject) => {
    let domainParams = params(~domainName=domainName, ());

    _checkDomainAvailability(service, domainParams, (error, data) => {
        switch (Js.toOption(error), Js.toOption(data)) {
        | (None, Some(result)) => {
          let availability = decodeResult(result |. availability);
          resolve(. availability);
        }
        | (Some(error), _) =>  reject(. error)
        | (None, None) => reject(. Route53DomainsError("No error and data recieved"))
        };
    }) |> ignore;

    ()
  });
};
