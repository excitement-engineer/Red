open ReasonReact;
open Utils;

requireCSS("./label.css");

let component = statelessComponent("CompletedLabel");

let make = (~completedCount, _children) => {
  ...component,
  render: (_self) => {
    let completedMessage = "#" ++ string_of_int(completedCount); 
      <label className="completedCount"> (stringToElement(completedMessage)) </label>
  }
};
