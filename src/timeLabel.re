Utils.requireCSS("./label.css");

let component = ReasonReact.statelessComponent("TimeLabel");

let make = (~secondsLeft, _children) => {
  ...component,
  render: (_self) => {
    let convertedTime = Utils.convertSecsToTime(secondsLeft);
    <label className="time"> (ReasonReact.stringToElement(convertedTime)) </label>
  }
};
