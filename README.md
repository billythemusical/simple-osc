# simple-osc

### So you wanna send data over the network??

This repo is aimed specifically at folks who wanna send data wirelessly over a wifi network.  Some of this applied to wired situations, but we have not tested for those situations.  Much of it is based on my work in interactive media while a student and research resident at NYU's ITP program.  

OSC stands for Open Sound Control, which speaks to its [origins](https://www.cnmat.berkeley.edu/opensoundcontrol) but is an acronym you can basically ignore.  OSC can be used for many different purposes where software programs or pieces of hardware need to exchange data.  

OSC is built upon the UDP network protocol.  UDP is great for sending data packets quickly, but there is no guarantee that or reporting if the message was received.  See below:

![tcp-vs-udp](images/tcp-vs-udp.jpg)

OSC allows sending data over a network, often wirelessly via Wifi.  It uses the UDP protocol, which is generally careless about individual messages, but has the added benefit of speed.  As such, OSC is often used in performance.

Many software programs like MaxMSP, TouchDesigner, Unity, and Unreal have OSC interfaces built into them.  Other platforms like Arduino and Node.js have programming libraries for sending and receiving OSC.



### Acknowledgements

This repo is inspired by Gene Kogan's [p5js-osc](https://github.com/genekogan/p5js-osc).  

OSC was originally developed at [CNMAT](https://www.cnmat.berkeley.edu/opensoundcontrol) by Adrian Freed, Matthew Wright, and others.  

The Arduino examples were slightly modified from the [Arduino/Teensy OSC repo](https://github.com/CNMAT/OSC) by Adrian Freed and Yotam Mann.
