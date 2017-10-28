open Notification;

open Audio;

[@bs.module] external alarmSound : string = "./sounds/alarm.mp3";

let register = () =>
  try (requestPermission()) {
  | _ => Js.log("Notifications not supported.")
  };

let alarm = (~title, ~message) => {
  let content: content = {"body": message};
  let notify = () => {
    ignore(Notification.make(title, content));
    let audio = Audio.make(alarmSound);
    play(audio);
    ignore(Js.Global.setTimeout(() => pause(audio), 2900))
  };
  try (notify()) {
  | _ => Js.log("Error sending notification.")
  }
};
