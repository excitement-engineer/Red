type audio;

external make : string => audio = "Audio" [@@bs.new];

external play : audio => unit = "play" [@@bs.send];

external pause : audio => unit = "pause" [@@bs.send];
