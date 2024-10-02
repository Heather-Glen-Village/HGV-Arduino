#include <SPI.h>
#include <Ethernet.h>

// Use a random, unique MAC address
byte mac[] = { 0xBE, 0x3D, 0x8E, 0xEF, 0xFE, 0xED };

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
