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

[@bs.deriving abstract]
type errorResponse = {
  message: string,
  code: string,
  time: string,
  requestId: string,
  statusCode: int,
  retryable: bool,
  retryDelay: float,
};

type callback = ((Js.Nullable.t(errorResponse), Js.Nullable.t(response)) => unit);

exception Route53DomainsError(string);

let decodeError = errorCode => switch errorCode {
| "InvalidInput" => InvalidInput
| "UnsupportedTLD" => UnsupportedTLD
| _ => InvalidInput
};

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
        | (Some(error), _) => reject(. Route53DomainsError(error |. code))
        | (None, None) => reject(. Route53DomainsError("No error and data recieved"))
        };
    }) |> ignore;

    ()
  });
};
