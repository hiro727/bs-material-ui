[@bs.deriving jsConverter]
type margin = [ | [@bs.as "dense"] `Dense];

[@bs.deriving jsConverter]
type variant = [
  | [@bs.as "standard"] `Standard
  | [@bs.as "outlined"] `Outlined
  | [@bs.as "filled"] `Filled
];

module Classes = {
  type classesType =
    | Root(string)
    | Error(string)
    | Disabled(string)
    | MarginDense(string)
    | Contained(string)
    | Focused(string)
    | Filled(string)
    | Required(string);
  type t = list(classesType);
  let to_string =
    fun
    | Root(_) => "root"
    | Error(_) => "error"
    | Disabled(_) => "disabled"
    | MarginDense(_) => "marginDense"
    | Contained(_) => "contained"
    | Focused(_) => "focused"
    | Filled(_) => "filled"
    | Required(_) => "required";
  let to_obj = listOfClasses =>
    listOfClasses->(
                     Belt.List.reduce(
                       Js.Dict.empty(),
                       (obj, classType) => {
                         switch (classType) {
                         | Root(className)
                         | Error(className)
                         | Disabled(className)
                         | MarginDense(className)
                         | Contained(className)
                         | Focused(className)
                         | Filled(className)
                         | Required(className) =>
                           Js.Dict.set(obj, to_string(classType), className)
                         };
                         obj;
                       },
                     )
                   );
};

[@bs.obj]
external makePropsMui:
  (
    ~children: 'children=?,
    ~className: string=?,
    ~disabled: bool=?,
    ~error: bool=?,
    ~filled: bool=?,
    ~focused: bool=?,
    ~margin: string=?,
    ~muiFormControl: Js.t({..})=?,
    ~required: bool=?,
    ~variant: string=?,
    ~key: string=?,
    ~classes: Js.Dict.t(string)=?,
    ~style: ReactDOMRe.Style.t=?,
    unit
  ) =>
  _ =
  "";

let makeProps =
    (
      ~children: option('children)=?,
      ~className: option(string)=?,
      ~disabled: option(bool)=?,
      ~error: option(bool)=?,
      ~filled: option(bool)=?,
      ~focused: option(bool)=?,
      ~margin: option(margin)=?,
      ~muiFormControl: option(Js.t({..}))=?,
      ~required: option(bool)=?,
      ~variant: option(variant)=?,
      ~key: option(string)=?,
      ~classes: option(Classes.t)=?,
      ~style: option(ReactDOMRe.Style.t)=?,
      (),
    ) =>
  makePropsMui(
    ~children?,
    ~className?,
    ~disabled?,
    ~error?,
    ~filled?,
    ~focused?,
    ~margin=?margin->(Belt.Option.map(v => marginToJs(v))),
    ~muiFormControl?,
    ~required?,
    ~variant=?variant->(Belt.Option.map(v => variantToJs(v))),
    ~key?,
    ~classes=?Belt.Option.map(classes, v => Classes.to_obj(v)),
    ~style?,
    (),
  );

[@bs.module "@material-ui/core"]
external make: React.component('a) = "FormHelperText";
