# simple-osc

### Sending data over the network

So you wanna send data over the network???

![tcp-vs-udp](images/tcp-vs-udp.jpg)

OSC stands for Open Sound Control, which speaks to its origins but is an acronym you can basically ignore.

OSC allows sending data over a network, often wirelessly via Wifi.  It uses the UDP protocol, which is generally careless about individual messages, but has the added benefit of speed.  As such, OSC is often used in performance.

Many software programs like MaxMSP, TouchDesigner, Unity, and Unreal have OSC interfaces built into them.  Other platforms like Arduino and Node.js have programming libraries for sending and receiving OSC.



### Acknowledgements

This repo is inspired by Gene Kogan's [p5js-osc](https://github.com/genekogan/p5js-osc).  

OSC was originally developed at [CNMAT](https://www.cnmat.berkeley.edu/opensoundcontrol) by Adrian Freed, Matthew Wright, and others.  

The Arduino examples were slightly modified from the [Arduino/Teensy OSC repo](https://github.com/CNMAT/OSC) by Adrian Freed and Yotam Mann.
