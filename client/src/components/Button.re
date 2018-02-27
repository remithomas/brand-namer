let component = ReasonReact.statelessComponent("Button");

type buttonType = 
  | Button
  | Submit;

let make = (~type_: buttonType, children) => {
  ...component,

  render: (_self) => {
    let theButtonType = 
      switch (type_) {
      | Button => "button"
      | Submit => "submit"
      };

    (
      <button className="button" _type=theButtonType>
        <div className="button-wrapper">
          {children[0]}
        </div>
      </button>
    );
  } 
};
