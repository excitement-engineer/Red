open ReasonReact;

open Utils;

requireCSS("./label.css");

let component = statelessComponent("Footer");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className="footerText grey">
      <label> (stringToElement("Created by ")) </label>
      <a className="red" href="https://github.com/excitement-engineer/Red" target="_blank">
        (stringToElement("excitement-engineer"))
      </a>
    </div>
};
