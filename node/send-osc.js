import { Client } from 'node-osc'

// ip for your computer, aka localhost
var ip = '127.0.0.1'
var port = 9999;

// pass in the ip and port as well as a callback to fire at the end
// in this case, the callback is using the anonymous function syntax '() => {}'
const oscClient = new Client(ip, port, () => {
  console.log(`OSC Client sending on port ${port}`)
})

// normal osc syntax is '/address' first and then your 'message',
// but you can send a message without address like so
// oscClient.send('hello', () => {...
oscClient.send('/address', 'hello', () => {
  oscClient.close()
})
