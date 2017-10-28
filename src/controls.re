open Utils;

open ReasonReact;

requireCSS("./controls.css");

[@bs.module] external playIcon : string = "./svg/pause.svg";

[@bs.module] external pauseIcon : string = "./svg/play.svg";

let component = statelessComponent("Controls");

type control =
  | Play
  | Pause;

let make = (~mode, ~onClick, _children) => {
  ...component,
  render: (_self) => {
    let icon =
      switch mode {
      | Play => playIcon
      | Pause => pauseIcon
      };
    <div className="control" onClick> <img src=icon alt="controls" /> </div>
  }
};
