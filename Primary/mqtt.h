#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "conf.h"

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
  
  if (command == "LED") {
    digitalWrite(LED, !digitalRead(2));
  }
  else if (command == "RELAY-ON")
  {
    digitalWrite(Relay, HIGH);
  }
  else if (command == "RELAY-OFF") {
    digitalWrite(Relay, LOW);
  }
  

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

void sendData(PubSubClient client, bool discreteInputs[NumSecondary][DIAddress], float FloatRegisters[NumSecondary][IRAddress/2]) {
  //turn data into a Json and Send it to NodeRed
  StaticJsonDocument<256> doc; // We going to need a bigger Json
  char output[300]; // should be like 10%  bigger then the JSON I Belive

  // Populate the JSON object
  for (int i = 0; i < NumSecondary; i++) {
    String key = "secondary" + String(i + 1);  // Create keys like "secondary1", "secondary2", etc.
    JsonArray row = doc.createNestedArray(key);  // Add a nested array with the key
    for (int j = 0; j < IRAddress/2; j++) {
      row.add(FloatRegisters[i][j]);  // Add values to the array
    }
  }

  serializeJson(doc, output);
  client.publish("hello",output);
}
