/*
 
 Based on work by Don Coleman and Tom Igoe

 
 */
 
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

// Accell stuff
#include <Arduino_LSM6DS3.h>
#include <MadgwickAHRS.h>

// initialize a Madgwick filter:
Madgwick filter;
// sensor's sample rate is fixed at 104 Hz:
const float sensorRate = 104.00;

// values for orientation:
float roll = 0.0;
float pitch = 0.0;
float heading = 0.0;
float deltaYGyro = 400;

// Wifi and OSC stuff
int status = WL_IDLE_STATUS;
#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)


char packetBuffer[255]; //buffer to hold incoming packet
char  ReplyBuffer[] = "/test ";       // a string to send back

WiFiUDP Udp;

// OSC Stuffs
const IPAddress outIp(192,168,8,210);        // remote IP of your computer
const unsigned int outPort = 12030;          // remote port to receive OSC
const unsigned int remotePort = 2390;          // local port to receive OSC
//String mills;

//LED STUFF
OSCErrorCode error;
unsigned int ledState = HIGH;              // LOW means led is *on*
#define LED_PIN 2


void setup() {
  ledSetup();
//  accelSetup();
  wifiSetup();
}

void loop() {
//  accelLoop();
  oscRead();
//  printOsc();
//  printAccel();
}

void ledSetup(){
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);    // turn *on* led
}

void led(OSCMessage &msg) {
  ledState = msg.getInt(0);
  digitalWrite(LED_PIN, ledState);
  Serial.print("/led: ");
  Serial.println(ledState);
}

void oscRead(){
  OSCMessage msg;
  int size = Udp.parsePacket();

  if (size > 0) {
    while (size--) {
      msg.fill(Udp.read());
    }
    if (!msg.hasError()) {
      msg.dispatch("/led", led);
    } else {
      error = msg.getError();
      Serial.print("error: ");
      Serial.println(error);
    }
  }  
}

void accelSetup() {
  
  // attempt to start the IMU:
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU");
//     stop here if you can't access the IMU:
    while (true);
  }
  // start the filter to run at the sample rate:
  filter.begin(sensorRate);
  Serial.println("test");
  
}

void accelLoop() {
  //accel stuff
  float xAcc, yAcc, zAcc;
  float xGyro, yGyro, zGyro;

  // check if the IMU is ready to read:
  if (IMU.accelerationAvailable() &&
      IMU.gyroscopeAvailable()) {
    // read accelerometer & gyrometer:
    IMU.readAcceleration(xAcc, yAcc, zAcc);
    IMU.readGyroscope(xGyro, yGyro, zGyro);

    // update the filter, which computes orientation:
    filter.updateIMU(xGyro, yGyro, zGyro, xAcc, yAcc, zAcc);

    // print the heading, pitch and roll
    roll = filter.getRoll();
    pitch = filter.getPitch();
    heading = filter.getYaw();

    if (yGyro > deltaYGyro)
    {
      Serial.println("flicked up");
      oscSend("/pitch", pitch);
    }
    else if (yGyro < -deltaYGyro) 
    {
      Serial.println("flicked down"); 
    }
  }
}

void oscSend(String addy, float val) {
    const char *addr = addy.c_str();
    OSCMessage msg(addr);
    msg.add(val);
    Udp.beginPacket(outIp, outPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
//    delay(10);
}

void printOsc() {
    Serial.print("sent ");
    Serial.print(pitch);
    Serial.print(" to ");
    Serial.print(outIp);
    Serial.print(" on port ");
    Serial.println(outPort);
}


 void printAccell () {  
    Serial.print("heading ");
    Serial.print(heading);
    Serial.print(", pitch ");
    Serial.print(pitch);
    Serial.print(", roll ");
    Serial.println(roll);
}

void wifiSetup() {
   //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(1000);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  Udp.begin(outPort);
 }

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
