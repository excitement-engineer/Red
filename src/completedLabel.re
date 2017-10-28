open ReasonReact;
open Utils;

requireCSS("./label.css");

[@bs.module] external historyIcon : string = "./svg/history.svg";

let component = statelessComponent("CompletedLabel");

let make = (~completedCount, _children) => {
  ...component,
  render: (_self) => {
    let completedMessage = "#" ++ string_of_int(completedCount); 
      <label className="completedCount"> (stringToElement(completedMessage)) </label>
  }
};
