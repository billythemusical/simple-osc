// Based on work by Don Coleman, Tom Igoe, & Yotam Mann 

#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

// Wifi and OSC stuff
int status = WL_IDLE_STATUS;

#include "arduino_secrets.h" // enter your sensitive data in arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)


WiFiUDP Udp;

// OSC Stuffs
const IPAddress outIp(192,168,1,100);       // remote IP of your computer
const unsigned int outPort = 9999;          // remote port to receive OSC
const unsigned int remotePort = 2390;       // local port to receive OSC (not used here)

void setup() {
  
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID :: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass); // For WPA/WPA2 network only
    delay(1000);
  }

  // print the SSID of the network you're attached to:
  Serial.println("Connected to the network!");
  Serial.print("SSID :: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("Board IP Address :: ");
  Serial.println(ip);

  Udp.begin(outPort); // start the UDP connection
  
}

void loop() {
  // sensor stuff
  oscSend("/sensor1", millis());
  oscSend("/sensor2", 10);
}

void oscSend(String addy, float val) {
    const char *addr = addy.c_str();  // allows for generic addresses
    OSCMessage msg(addr);
    msg.add(val);
    Udp.beginPacket(outIp, outPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
}
