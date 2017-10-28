let module PauseIcon {
  open ReasonReact;

  let component = statelessComponent("Pause");

  let make = _children => {
    ...component,
    render: (_self) => {
      <svg
        fill="#000000" viewBox="0 0 24 24" width="100%" height="100%" xmlns="http://www.w3.org/2000/svg">
        <path d="M8 5v14l11-7z" />
        <path d="M0 0h24v24H0z" fill="none" />
      </svg>
    }
  };
};

let module PlayIcon {
  open ReasonReact;

  let component = statelessComponent("Play");

  let make = _children => {
    ...component,
    render: (_self) => {
      <svg fill="#000000" width="100%" height="100%" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg">
          <path d="M6 19h4V5H6v14zm8-14v14h4V5h-4z"/>
          <path d="M0 0h24v24H0z" fill="none"/>
      </svg>
    }
  };
};

open Utils;
open ReasonReact;

requireCSS("./controls.css");

let component = statelessComponent("Controls");

type control =
  | Play
  | Pause;

let make = (~mode, ~onClick, _children) => {
  ...component,
  render: (_self) => {
    let icon =
      switch mode {
      | Play => <PauseIcon />
      | Pause => <PlayIcon />
      }; 
    <div className="control" onClick> {icon} </div>
  }
};
