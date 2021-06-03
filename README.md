# simple-osc

## tl;dr take me to the examples

[Arduino](arduino/)
[MaxMSP](max-msp/)
[Ableton Live + M4L](ableton-live/)
[Node.js](node/)


### So you wanna send data over the network??

This repo is aimed specifically at folks who wanna send data wirelessly (and not use BLE).  FYI will require a wifi network.  Much of this is based on my work in interactive media while a student and research resident at NYU's ITP/IMA program.   

Note: some of these examples can be used in wired situations, but they have not been tested.

### What is OSC?

OSC stands for Open Sound Control, which speaks to its [origins](https://www.cnmat.berkeley.edu/opensoundcontrol) but is an acronym you can basically ignore.  OSC can be used for many different purposes where software programs or pieces of hardware need to communicate.

OSC is built upon the UDP network protocol.  UDP is great for sending data quickly, but and because there is no guarantee that or reporting if the message was received.  See below:

![tcp-vs-udp](images/tcp-vs-udp.jpg)

For these reasons, game engines utilize UDP's speed to send game state information.  So UDP should only be used when losing the occasional message is not critical like, for example, in a performance using continuous values from an accelerometer.

For single, discreet messages over a network, like sending messages in a chat interface or to an IoT device that opens your front door, it's best to use something based on the TCP protocol, like `http requests`, or even [MQTT](https://mqtt.org/getting-started/) which is UDP under the hood.  These will more or less guarantee delivery and receipt.  

### What programs use OSC?

Many software programs like MaxMSP, TouchDesigner, Unity, and Unreal have OSC interfaces built into them.  Other platforms like Arduino and Node.js have programming libraries for sending and receiving OSC.  I have tried to give useful and tl;dr examples here.

### Acknowledgements

This repo is inspired by Gene Kogan's [p5js-osc](https://github.com/genekogan/p5js-osc).  

OSC was originally developed at [CNMAT](https://www.cnmat.berkeley.edu/opensoundcontrol) by Adrian Freed, Matthew Wright, and others.  

The Arduino examples were slightly modified from the [Arduino/Teensy OSC repo](https://github.com/CNMAT/OSC) by Adrian Freed and Yotam Mann.
