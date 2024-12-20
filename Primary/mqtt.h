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
  
  if (topic == "ArduinoCMD") {
    if (command == "LED") {
      digitalWrite(LED, !digitalRead(2));
    }
    // else if (command == "RELAY-ON")
    // {
    //   digitalWrite(Relay, HIGH);
    // }
    // else if (command == "RELAY-OFF") {
    //   digitalWrite(Relay, LOW);
    // }
  }

}

PubSubClient& reconnected(PubSubClient& client) {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient", MQTTUser, MQTTPassword)) {
      Serial.println("connected");
      client.subscribe(ArduinoCMD); //Used to Send command to the Boards
      client.subscribe(temprequest+PrimaryNum);
      client.publish(bootmessage, "MQTT Is Made and Ready to Send Data - Primary "+(PrimaryNum));
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

void sendData(PubSubClient client, bool discreteInputs[NumSecondary][DIAddress], float FloatRegisters[NumSecondary][IRAddress/2], bool Smoke) {
  //turn data into a Json and Send it to NodeRed

  StaticJsonDocument<256> doc; // We going to need a bigger Json
  char SensorJson[300]; // should be like 10%  bigger then the JSON I Think

  // Create Json for Every Secondary
  for (int s = 0; s < NumSecondary; s++)
  {
    doc["Primary"] = PrimaryNum;
    doc["Secondary"] = s+1;

    // Float Register
    JsonArray FR = doc.createNestedArray("FR");
    for (int a = 0; a < IRAddress/2; a++) {
      FR.add(FloatRegisters[s][a]);
    }

    // Discrete Inputs
    JsonArray DI = doc.createNestedArray("DI");
    for (int a = 0; a < DIAddress; a++) {
      DI.add(discreteInputs[s][a]);
    }

    // Serialize JSON to a string and print it
    serializeJson(doc, SensorJson);
    client.publish(SensorTopic,SensorJson);
    doc.clear();
  }
  // Json for the Primary
  doc["Primary"] = PrimaryNum;
  doc["Smoke"] = Smoke;

  serializeJson(doc, SensorJson);
  client.publish(SensorTopic,SensorJson);
  doc.clear();
}
