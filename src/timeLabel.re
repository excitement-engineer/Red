Utils.requireCSS "./timeLabel.css";

let component = ReasonReact.statelessComponent "ModeButton";

let make ::secondsLeft _children => {
  ...component,
  render: fun _self => {
    let convertedTime = Utils.convertSecsToTime secondsLeft;
    <label className="time"> (ReasonReact.stringToElement convertedTime) </label>
  }
};
