import { Server } from 'node-osc'
var ip = '0.0.0.0'
var port = 9999;


var oscServer = new Server(port, ip, () => {
  console.log(`OSC Server is listening on port ${port}`);
});

oscServer.on('message', function (msg) {
  let num = msg.parseInt();
  if (num) {
    console.log(`Message: ${num}`);
  } else {
    console.log("what's this?")
  }
});
