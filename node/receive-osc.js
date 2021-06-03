import { Server } from 'node-osc'

// ip for your computer, aka localhost
var ip = '127.0.0.1'
var port = 9999;

// pass in the port and ip as well as a callback to fire at the end
// in this case, the callback is using the anonymous function syntax '() => {}'
var oscServer = new Server(port, ip, () => {
  console.log(`OSC Server is listening on port ${port}`)
})

// if the message has an address or multiple messages,
// they arrive in an array
oscServer.on('message', (msg) => {
  console.log(msg)
})
