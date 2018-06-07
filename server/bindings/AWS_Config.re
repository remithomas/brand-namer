[@bs.deriving abstract]
type config = {
  [@bs.optional] endpoint: string,
  [@bs.optional] accessKeyId: string,
  [@bs.optional] secretAccessKey: string,
  apiVersion: string,
  region: string
};
