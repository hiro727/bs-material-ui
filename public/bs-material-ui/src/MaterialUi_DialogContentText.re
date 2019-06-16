[@bs.deriving jsConverter]
type align = [
  | [@bs.as "inherit"] `Inherit
  | [@bs.as "left"] `Left
  | [@bs.as "center"] `Center
  | [@bs.as "right"] `Right
  | [@bs.as "justify"] `Justify
];

[@bs.deriving jsConverter]
type color = [
  | [@bs.as "initial"] `Initial
  | [@bs.as "inherit"] `Inherit
  | [@bs.as "primary"] `Primary
  | [@bs.as "secondary"] `Secondary
  | [@bs.as "textPrimary"] `TextPrimary
  | [@bs.as "textSecondary"] `TextSecondary
  | [@bs.as "error"] `Error
];

[@bs.deriving jsConverter]
type display = [
  | [@bs.as "initial"] `Initial
  | [@bs.as "block"] `Block
  | [@bs.as "inline"] `Inline
];

[@bs.deriving jsConverter]
type variant = [
  | [@bs.as "h1"] `H1
  | [@bs.as "h2"] `H2
  | [@bs.as "h3"] `H3
  | [@bs.as "h4"] `H4
  | [@bs.as "h5"] `H5
  | [@bs.as "h6"] `H6
  | [@bs.as "subtitle1"] `Subtitle1
  | [@bs.as "subtitle2"] `Subtitle2
  | [@bs.as "body1"] `Body1
  | [@bs.as "body2"] `Body2
  | [@bs.as "caption"] `Caption
  | [@bs.as "button"] `Button
  | [@bs.as "overline"] `Overline
  | [@bs.as "srOnly"] `SrOnly
  | [@bs.as "inherit"] `Inherit
];

module Classes = {
  type classesType =
    | Root(string);
  type t = list(classesType);
  let to_string =
    fun
    | Root(_) => "root";
  let to_obj = listOfClasses =>
    listOfClasses->(
                     Belt.List.reduce(
                       Js.Dict.empty(),
                       (obj, classType) => {
                         switch (classType) {
                         | Root(className) =>
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
    ~key: string=?,
    ~align: string=?,
    ~className: string=?,
    ~color: string=?,
    ~display: string=?,
    ~gutterBottom: bool=?,
    ~noWrap: bool=?,
    ~paragraph: bool=?,
    ~theme: Js.t({..})=?,
    ~variant: string=?,
    ~variantMapping: Js.t({..})=?,
    ~classes: Js.Dict.t(string)=?,
    ~style: ReactDOMRe.Style.t=?,
    unit
  ) =>
  _ =
  "";

let makeProps =
    (
      ~children: option('children)=?,
      ~key: option(string)=?,
      ~align: option(align)=?,
      ~className: option(string)=?,
      ~color: option(color)=?,
      ~display: option(display)=?,
      ~gutterBottom: option(bool)=?,
      ~noWrap: option(bool)=?,
      ~paragraph: option(bool)=?,
      ~theme: option(Js.t({..}))=?,
      ~variant: option(variant)=?,
      ~variantMapping: option(Js.t({..}))=?,
      ~classes: option(Classes.t)=?,
      ~style: option(ReactDOMRe.Style.t)=?,
      (),
    ) =>
  makePropsMui(
    ~children?,
    ~key?,
    ~align=?align->(Belt.Option.map(v => alignToJs(v))),
    ~className?,
    ~color=?color->(Belt.Option.map(v => colorToJs(v))),
    ~display=?display->(Belt.Option.map(v => displayToJs(v))),
    ~gutterBottom?,
    ~noWrap?,
    ~paragraph?,
    ~theme?,
    ~variant=?variant->(Belt.Option.map(v => variantToJs(v))),
    ~variantMapping?,
    ~classes=?Belt.Option.map(classes, v => Classes.to_obj(v)),
    ~style?,
    (),
  );

[@bs.module "@material-ui/core"]
external make: React.component('a) = "DialogContentText";
