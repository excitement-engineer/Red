type time = {
  hours: int,
  minutes: int,
  seconds: int
};

let convertSecsToTime = (seconds) => {
  let minutes = seconds / 60;
  let secondsRemaining = seconds mod 60;
  let minutesRemaining = minutes mod 60;
  let formatTime = (time) => {
    let formattedTime =
      if (time < 10) {
        "0" ++ string_of_int(time)
      } else {
        string_of_int(time)
      };
    formattedTime
  };
  let formattedSeconds = formatTime(secondsRemaining);
  let formattedMinutes = formatTime(minutesRemaining);
  let timer = formattedMinutes ++ (":" ++ formattedSeconds);
  timer
};

[@bs.val] external requireCSS : string => unit = "require";
