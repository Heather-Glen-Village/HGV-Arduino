#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include "conf.h"

// Connects to Router via Ethernet
void EthConnect()
{
  byte mac[] = MAC_ADDRESS;
  if (Ethernet.begin(mac) == 0)
  {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Prints Reason for Failure 
    if (Ethernet.hardwareStatus() == EthernetNoHardware)
    {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    }
    else if (Ethernet.linkStatus() == LinkOFF)
    {
      Serial.println("Ethernet cable is not connected.");
    }
    while(true) { // Not Primary Board Thefore Don't Continue Code
    Serial.println("Board is most likely not the Priamry Board");
    delay(1000);
    }
  }
  else
  {
    Serial.println(Ethernet.localIP());
    Serial.println("This is a Priamry Board");
  }
}

// What to Do when Getting a Message from MQTT
void callback(char *topic, byte *message, unsigned int length)
{
  Serial.print("Message received on topic: ");
  Serial.println(topic);

  // Turns Message into a String
  String command = "";
  for (unsigned int i = 0; i < length; i++)
  {
    command += (char)message[i];
  }

  // For Debug can be remove if needed
  Serial.print("Command Received: ");
  Serial.println(command);

  // Unused
  if (topic == "ArduinoCMD")
  {
    if (command == "LED")
    {
      digitalWrite(LED, !digitalRead(2));
    }
  }
}

PubSubClient &reconnected(PubSubClient &client)
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("arduinoClient", MQTTUser, MQTTPassword))
    {
      Serial.println("connected");
      client.subscribe(ArduinoCMD); // Used to Send command to the Boards (Unused)
      client.subscribe(temprequest + PrimaryNum); // Lisiting to Personal Topic for Tempature (BTW should mention this but right now alot of the MQTT is unsecure and therorically if someone were to get the password anyone could mess with anyone room)
      client.publish(bootmessage, "MQTT Is Made and Ready to Send Data - Primary " + (PrimaryNum));
      return client;
    }
    else
    {
      // Wait 5 seconds before retrying
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
