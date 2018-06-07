/* From https://docs.aws.amazon.com/Route53/latest/APIReference/CommonErrors.html */

type t = 
  | AccessDeniedException
  | IncompleteSignature
  | InternalFailure
  | InvalidAction
  | InvalidClientTokenId
  | InvalidParameterCombination
  | InvalidParameterValue
  | InvalidQueryParameter
  | MalformedQueryString
  | MissingAction
  | MissingAuthenticationToken
  | MissingParameter
  | OptInRequired
  | RequestExpired
  | ServiceUnavailable
  | ThrottlingException
  | ValidationError;

[@bs.deriving abstract]
type responseError = {
  statusCode: int,
  code: string,
  message: string,
  requestId: string,
  retryable: bool,
  retryDelay: float,
};
