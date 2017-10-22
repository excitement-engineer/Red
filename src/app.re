open Utils;

open ReasonReact;

requireCSS "./app.css";

type mode =
  | Pomodoro
  | LongBreak
  | ShortBreak;

type action =
  | TogglePausePlay
  | Tick
  | StartShortBreak
  | StartLongBreak
  | StartPomodoro;

type state = {
  paused: bool,
  count: int,
  timerId: ref (option Js.Global.intervalId),
  mode
};

let pomodoroTime = 25 * 60;

let shortBreak = 5 * 60;

let longBreak = 15 * 60;

let component = reducerComponent "App";

let make _children => {
  ...component,
  initialState: fun () => {mode: Pomodoro, paused: false, count: pomodoroTime, timerId: ref None},
  reducer: fun action state =>
    switch action {
    | TogglePausePlay => Update {...state, paused: not state.paused}
    | Tick =>
      let newCount =
        if state.paused {
          state.count
        } else if (state.count == 0) {
          0
        } else {
          state.count - 1
        };
      Update {...state, count: newCount}
    | StartShortBreak => Update {...state, mode: ShortBreak, count: shortBreak}
    | StartLongBreak => Update {...state, mode: LongBreak, count: longBreak}
    | StartPomodoro => Update {...state, mode: Pomodoro, count: pomodoroTime}
    },
  didMount: fun self => {
    Alarm.register ();
    self.state.timerId := Some (Js.Global.setInterval (self.reduce (fun _ => Tick)) 1000);
    NoUpdate
  },
  didUpdate: fun {oldSelf, newSelf} =>
    if (oldSelf.state.count > 0 && newSelf.state.count == 0) {
      let message =
        switch newSelf.state.mode {
        | Pomodoro => "You finished your pomodoro! Time for a break!"
        | LongBreak => "Relax time is up! Time for some work!"
        | ShortBreak => "Break's done, time for some work!"
        };
      Alarm.alarm ::message title::"Time's up"
    },
  willUnmount: fun {state} =>
    switch !state.timerId {
    | Some id => Js.Global.clearInterval id
    | _ => ()
    },
  render: fun {state, reduce} => {
    let mode = state.paused == true ? Controls.Play : Controls.Pause;
    <div className="app">
      <div className="container">
        <TimeLabel secondsLeft=state.count />
        <div className="control_container">
          <Controls mode onClick=(reduce (fun _ => TogglePausePlay)) />
        </div>
        <div className="modes_container">
          <ModeButton
            selected=(state.mode == Pomodoro)
            onClick=(reduce (fun _ => StartPomodoro))
            label="work"
          />
          <ModeButton
            selected=(state.mode == ShortBreak)
            onClick=(reduce (fun _ => StartShortBreak))
            label="break"
          />
          <ModeButton
            selected=(state.mode == LongBreak)
            onClick=(reduce (fun _ => StartLongBreak))
            label="relax"
          />
        </div>
      </div>
    </div>
  }
};
