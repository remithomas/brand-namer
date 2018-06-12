open ReBemHelper;

let component = ReasonReact.statelessComponent("Button");

type buttonType = 
  | Button
  | Submit;

let make = (
  ~type_: buttonType = Button,
  ~className="",
  children
) => {
  ...component,

  render: (_self) => {
    let theButtonType = 
      switch (type_) {
      | Button => "button"
      | Submit => "submit"
      };

    let bemClasses = bem(
      ~block="button",
      ~modifiers=[String(theButtonType)],
      ()
    );

    (
      <button className=(bemClasses ++ " " ++ className) _type=theButtonType>
        <div className="button-wrapper">
          {children[0]}
        </div>
      </button>
    );
  } 
};
