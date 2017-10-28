type audio;
type path = string;

[@bs.new] external make : path => audio = "Audio";

[@bs.send] external play : audio => unit = "play";

[@bs.send] external pause : audio => unit = "pause";
