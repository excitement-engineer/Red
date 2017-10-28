Utils.requireCSS("./modeButton.css");

let component = ReasonReact.statelessComponent("ModeButton");

let make = (~selected, ~onClick, ~label, _children) => {
  ...component,
  render: (_self) => {
    let classNames = "mode_button" ++ (selected ? " mode_button_selected" : "");
    <button className=classNames onClick>
      (ReasonReact.stringToElement(String.uppercase(label)))
    </button>
  }
};
