open Utils;

open ReasonReact;

requireCSS "./controls.css";

external playIcon : string = "./svg/pause.svg" [@@bs.module];

external pauseIcon : string = "./svg/play.svg" [@@bs.module];

let component = statelessComponent "Controls";

type control =
  | Play
  | Pause;

let make ::mode ::onClick _children => {
  ...component,
  render: fun _self => {
    let icon =
      switch mode {
      | Play => playIcon
      | Pause => pauseIcon
      };
    <div className="control" onClick> <img src=icon alt="controls" /> </div>
  }
};
