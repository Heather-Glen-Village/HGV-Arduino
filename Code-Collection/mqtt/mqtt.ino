#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

#define MAC_ADDRESS {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF}
#define server { 192, 168, 3, 126 }
#define MQTTUser "arduino"
#define MQTTPassword "arduino"


EthernetClient ethClient;


void EthConnect() {
  byte mac[] = MAC_ADDRESS;
  //check if We can get internet connection Just for testing 
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    } 
    else if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
      // while(true) { // no point in carrying on, so do nothing forevermore:
        Serial.println("Board is most likely not the Priamry Board");
        delay(1000);
      // }  
  }
    else {
    Serial.println(Ethernet.localIP());
    Serial.println("This is a Priamry Board");
  }
}


void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.println(topic);

  String command = "";
  for (unsigned int i = 0; i < length; i++) {
    command += (char)message[i];
  }

// For Testing Remove Later so that modbus doesn't get messed Ups
  Serial.print("Command Received: ");
  Serial.println(command);
}

PubSubClient& reconnected(PubSubClient& client) {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient", MQTTUser, MQTTPassword)) {
      Serial.println("connected");
      client.subscribe("arduinoCMD"); //Used to Send command to the Boards
      client.publish("test", "Primary Board is Online");
      return client;
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


PubSubClient client(server, 1883, callback, ethClient);

void setup() {
  Serial.begin(9600);
  while (!Serial);
  EthConnect();
  Serial.println(F("MQTT test"));

}

void loop() {

  if (!client.connected()) {
    reconnected(client);
  }
  client.loop();
  StaticJsonDocument<32> doc;
  char output[55];

  Serial.println("Looping");
  while(Serial.available() == 0) {
    delay(100);
    client.loop();
  }
  Serial.read();
  int test = 5;
    doc["t"] = test;
    Serial.println("Read");

    serializeJson(doc, output);
    Serial.println(output);
    client.publish("hello", output);
    Serial.println("Sent");
  }
    