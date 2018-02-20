/* [%bs.raw {|require('./BrandNamerApp.scss')|}]; */

let component = ReasonReact.statelessComponent("BrandNamerApp");

let make = (children) => {
  ...component,
  render: (_self) =>
    <div className="BrandNamerApp">
      <div className="title"> (ReasonReact.stringToElement("Brand namer")) </div>
    </div>
};
