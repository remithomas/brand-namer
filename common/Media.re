type mediaType = 
  | Facebook
  | Website;

let formatFacebookName = name => "facebook.com/" ++ name;
let formatDomainName = name => name ++ ".com";

let encodeMediaType = type_ => switch type_ {
| Facebook => "facebook"
| Website => "website"
};
