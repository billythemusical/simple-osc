import { Server } from 'node-osc'
const { spawn } = require('child_process')

var wifi_ip = spawn('ipconfig getifaddr en0')
wifi_ip.on('data', (ip) => console.log(`WIFI IP: ${ip}`))

var ethernet_ip = spawn('ipconfig getifaddr en1')
ethernet_ip.on('data', (ip) => console.log(`ETHERNET IP: ${ip}`))

var port = 9999;



var oscServer = new Server(port, ip, () => {
  console.log(`OSC Server is listening on port ${port}`);
});

oscServer.on('message', function (msg) {
  console.log(`Message: ${msg}`);
  // oscServer.close();
});
