open ReBemHelper;

let component = ReasonReact.statelessComponent("Button");

type buttonType = 
  | Button
  | Submit;

let make = (~type_: buttonType = Button, children) => {
  ...component,

  render: (_self) => {
    let theButtonType = 
      switch (type_) {
      | Button => "button"
      | Submit => "submit"
      };

    (
      <button className=(bem(
        ~block="button",
        ~modifiers=[String(theButtonType)],
        ()
      )) _type=theButtonType>
        <div className="button-wrapper">
          {children[0]}
        </div>
      </button>
    );
  } 
};
