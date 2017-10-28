type notification;

type content = {. "body": string};

[@bs.new] external make : (string, content) => notification = "Notification";

[@bs.val] external requestPermission : unit => unit = "Notification.requestPermission";
