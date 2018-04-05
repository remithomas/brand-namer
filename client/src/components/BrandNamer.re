let component = ReasonReact.statelessComponent("BrandNamer");

let handleSubmitForm = (term) => {
  let apiUrlNamerTerm = Constants.apiUrlNamer ++ "/" ++ term;
  Js.Promise.(
    Axios.get(apiUrlNamerTerm)
    |> then_((response) => resolve(Js.log(response##data)))
    |> catch((error) => resolve(Js.log(error)))
  );
};

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className="brand-namer">
      <BrandNamerForm
        onSubmit=(value => handleSubmitForm(value) |> ignore)
      />
    </div>
};
