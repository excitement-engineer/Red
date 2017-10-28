open Utils;
open ReasonReact;

requireCSS("./app.css");

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
  timerId: ref(option(Js.Global.intervalId)),
  mode,
  completeCount: int
};

let secondsForMode = mode => switch(mode) {
    | Pomodoro => 25 * 60
    | ShortBreak => 5 * 60
    | LongBreak => 15 * 60
  };

let updateMode = state => {
  let completeCount = state.mode == Pomodoro ? state.completeCount + 1 : state.completeCount;
  
  let shouldUpdateToLongBreak = completeCount mod 4 == 0;

  let mode = switch(state.mode) {
      | Pomodoro => shouldUpdateToLongBreak ? LongBreak : ShortBreak
      | LongBreak => Pomodoro
      | ShortBreak => Pomodoro
  };

  UpdateWithSideEffects({...state, count: secondsForMode(mode), mode, completeCount, paused: true}, (_) => {
    let message =
      switch state.mode {
      | Pomodoro => "You finished your pomodoro! " ++ (shouldUpdateToLongBreak ? "Time to relax!" : "Time for a break!")
      | LongBreak => "Relax time is up! Time for some work!"
      | ShortBreak => "Break's done, time for some work!"
      };
    Alarm.alarm(~message, ~title="Time's up");
  });
};

let updateCount = state => {
  let count =
    if (state.paused) {
      state.count
    } else if (state.count == 0) {
      0
    } else {
      state.count - 1
    };
  Update({...state, count});
};

let component = reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => {mode: Pomodoro, paused: false, count: secondsForMode(Pomodoro), timerId: ref(None), completeCount: 0},
  reducer: (action, state) =>
    switch action {
    | TogglePausePlay => Update({...state, paused: ! state.paused})
    | Tick =>
      let taskFinished = state.count == 1  && !state.paused;
      if (taskFinished) {
        updateMode(state);
      } else {
        updateCount(state);
      };
    | StartShortBreak => Update({...state, mode: ShortBreak, count: secondsForMode(ShortBreak)})
    | StartLongBreak => Update({...state, mode: LongBreak, count: secondsForMode(LongBreak)})
    | StartPomodoro => Update({...state, mode: Pomodoro, count: secondsForMode(Pomodoro)})
    },
  didMount: (self) => {
    Alarm.register();
    self.state.timerId := Some(Js.Global.setInterval(self.reduce((_) => Tick), 1000));
    NoUpdate
  },
  willUnmount: ({state}) =>
    switch state.timerId^ {
    | Some(id) => Js.Global.clearInterval(id)
    | _ => ()
    },
  render: ({state, reduce}) => {
    let mode = state.paused ? Controls.Play : Controls.Pause;
    <div className="app">
      <div className="container">
        <TimeLabel secondsLeft=state.count />
        <div className="control_container">
          <Controls mode onClick=(reduce((_) => TogglePausePlay)) />
        </div>
        <div className="modes_container">
          <ModeButton
            selected=(state.mode == Pomodoro)
            onClick=(reduce((_) => StartPomodoro))
            label="work"
          />
          <ModeButton
            selected=(state.mode == ShortBreak)
            onClick=(reduce((_) => StartShortBreak))
            label="break"
          />
          <ModeButton
            selected=(state.mode == LongBreak)
            onClick=(reduce((_) => StartLongBreak))
            label="relax"
          />
        </div>
        <CompletedLabel completedCount=state.completeCount />
      </div>
    </div>
  }
};
