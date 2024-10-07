#include <SPI.h>
#include <Ethernet.h>

// Use a random, unique MAC address C2:A2:DF:70:D8:44
byte mac[] = { 0xC2, 0xA2, 0xDF, 0x70, 0xD8, 0x44 };

// Set a static IP address (ensure it's within your network's range)
IPAddress ip(192, 168, 3, 87); // Adjust to match your network

EthernetClient client;

void setup() {
  // start the serial library:
  Serial.begin(9600);

  // start the Ethernet connection with a static IP:
  Ethernet.begin(mac, ip);

  // print your local IP address:
  Serial.print("Static IP Address: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // Add code for your Ethernet logic here
}
