[@bs.deriving jsConverter]
type color = [
  | [@bs.as "primary"] `Primary
  | [@bs.as "secondary"] `Secondary
];

[@bs.deriving jsConverter]
type margin = [
  | [@bs.as "none"] `None
  | [@bs.as "dense"] `Dense
  | [@bs.as "normal"] `Normal
];

[@bs.deriving jsConverter]
type variant = [
  | [@bs.as "standard"] `Standard
  | [@bs.as "outlined"] `Outlined
  | [@bs.as "filled"] `Filled
];

module Classes = {
  type classesType =
    | Root(string)
    | MarginNormal(string)
    | MarginDense(string)
    | FullWidth(string);
  type t = list(classesType);
  let to_string =
    fun
    | Root(_) => "root"
    | MarginNormal(_) => "marginNormal"
    | MarginDense(_) => "marginDense"
    | FullWidth(_) => "fullWidth";
  let to_obj = listOfClasses =>
    listOfClasses->(
                     Belt.List.reduce(
                       Js.Dict.empty(),
                       (obj, classType) => {
                         switch (classType) {
                         | Root(className)
                         | MarginNormal(className)
                         | MarginDense(className)
                         | FullWidth(className) =>
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
    ~color: string=?,
    ~component: 'union_r0ea=?,
    ~disabled: bool=?,
    ~error: bool=?,
    ~fullWidth: bool=?,
    ~hiddenLabel: bool=?,
    ~margin: string=?,
    ~required: bool=?,
    ~variant: string=?,
    ~key: string=?,
    ~ref: ReactDOMRe.domRef=?,
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
      ~color: option(color)=?,
      ~component:
         option(
           [
             | `String(string)
             | `Callback(unit => React.element)
             | `Element(React.element)
           ],
         )=?,
      ~disabled: option(bool)=?,
      ~error: option(bool)=?,
      ~fullWidth: option(bool)=?,
      ~hiddenLabel: option(bool)=?,
      ~margin: option(margin)=?,
      ~required: option(bool)=?,
      ~variant: option(variant)=?,
      ~key: option(string)=?,
      ~ref: option(ReactDOMRe.domRef)=?,
      ~classes: option(Classes.t)=?,
      ~style: option(ReactDOMRe.Style.t)=?,
      (),
    ) =>
  makePropsMui(
    ~children?,
    ~className?,
    ~color=?color->(Belt.Option.map(v => colorToJs(v))),
    ~component=?
      component->(Belt.Option.map(v => MaterialUi_Helpers.unwrapValue(v))),
    ~disabled?,
    ~error?,
    ~fullWidth?,
    ~hiddenLabel?,
    ~margin=?margin->(Belt.Option.map(v => marginToJs(v))),
    ~required?,
    ~variant=?variant->(Belt.Option.map(v => variantToJs(v))),
    ~key?,
    ~ref?,
    ~classes=?Belt.Option.map(classes, v => Classes.to_obj(v)),
    ~style?,
    (),
  );

[@bs.module "@material-ui/core"]
external make: React.component('a) = "FormControl";
