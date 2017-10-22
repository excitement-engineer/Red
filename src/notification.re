type notification;

type content = Js.t {. body : string};

external make : string => content => notification = "Notification" [@@bs.new];

external requestPermission : unit => unit = "Notification.requestPermission" [@@bs.val];
