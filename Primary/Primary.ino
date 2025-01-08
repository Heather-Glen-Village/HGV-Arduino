/*
  Primary Arduino Control

  This sketch is the Code That lets the Priamry Act as a ModbusRTC Master which gather data from other Arduino and send them to a Another Service using MQTT. this Arduino should also be able to take in message from a webapp and being able to control the temperature of the room.

  Pin List
    - D0 RX
    - D1 TX
    - D2 LED
    - D3 Smoke
    - D4 Heat On
    - D5 Water Off
    - D6 Power Off
    - D7 Cool On
    - D8 Eth-Int
    - D10 Eth-CSN
    - D11 Eth-MOSI
    - D12 Eth-MISO
    - D13 Eth-SCK


Modbus Address
Coil Address Index
 - (0) Command to Read Sensors

Input Register/Float Register Address Index (InputRegister)[FloatRegister]
 - (0-1)[0] Temperature from DS18B20
 - (2-5)[1-2] Temperature and Humidity from AM2302

Discrete Inputs Address Index
 - (0) Motion Sensor
 - (1) Water Leak Sensor
 - (2) Vibration Sensor

Data from Primary
  - Smoke Alarm
  - Water?
  - Set Temp?

  Created on November 11, 2024
  By Zachary Schultz
*/

// Initializing libraries
#include <SPI.h>
#include <Ethernet.h>
#include <ModbusRTUMaster.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Importing .h files
#include "conf.h"
#include "errorcheck.h"
#include "mqtt.h"
#include "json.h"

//Basic init for Commuination Library
ModbusRTUMaster modbus(RS485Serial); // DERE Pins aren't used with our RS485 so they do not have to be define 
EthernetClient ethClient;
PubSubClient client(server, port, callback, ethClient);

// Modbus Arrays Numbers come from conf.h
bool Coils[NumSecondary][CoilAddress];
bool DiscreteInputs[NumSecondary][DIAddress];
uint16_t HoldingRegisters[NumSecondary][HRAddress];
uint16_t InputRegisters[NumSecondary][IRAddress];
float (*FloatRegisters)[IRAddress / 2] = (float (*)[IRAddress / 2]) InputRegisters; // Turns an array of uint16 into floats by taking array in pairs

//Temp Varable until we get real smoke data
bool Smoke = 1;

void readSensors()
{
  Serial.println("Telling Secondarys to Read Sensors");
  errorCheck(modbus.writeSingleCoil(0, 0, 1)); // Tells All Secondary to Read Sensors

  // Temp Primary Senors until really ones get added
  Smoke = 1;

  delay(5000); // wait for Sensors to Read and Serial to Clear (COULD BE SHORTEN/REMOVED IF NEEDED)

  // Collects All Sensor Data from Secondary
  for (int i = 0; i < NumSecondary; i++)
  {
    errorCheck(modbus.readDiscreteInputs(i + 1, 0, DiscreteInputs[i], DIAddress));
    delay(100);
  }
  for (int i = 0; i < NumSecondary; i++)
  {
    errorCheck(modbus.readInputRegisters(i + 1, 0, InputRegisters[i], IRAddress));
    delay(100);
  }
}

//Used just for Debug really isn't needed and could be remove
void printdata()
{
  
  Serial.println("-----Discrete Input-----");
  for (int i = 0; i < NumSecondary; i++)
  {
    for (int z = 0; z < DIAddress; z++)
    {
      Serial.print(DiscreteInputs[i][z]);
      Serial.print(",");
      delay(100);
    }
    Serial.println();
  }
  delay(2000);
  Serial.println("-----RAW Input Register-----");
  for (int i = 0; i < NumSecondary; i++)
  {
    for (int z = 0; z < IRAddress; z++)
    {
      Serial.print(InputRegisters[i][z]);
      Serial.print(",");
      delay(100);
    }
    Serial.println();
  }
  delay(2000);
  Serial.println("-----Float Register-----");
  for (int i = 0; i < NumSecondary; i++)
  {
    for (int z = 0; z < IRAddress / 2; z++)
    {
      Serial.print(FloatRegisters[i][z]);
      Serial.print(",");
      delay(100);
    }
    Serial.println();
  }
}

// ----------Basic Setup and Loop Start Here ----------
void setup()
{
  // Starts all Serial and Modbus Communication
  Serial.begin(baud); 
  RS485Serial.begin(baud); // Only Needed if using Software Serial or have 2 Serial Terminals
  modbus.begin(baud); 
  pinMode(LED, OUTPUT);
  Serial.println("Primary Board Sketch");
  EthConnect();
  delay(1000);
  
}

void loop()
{
  // Reconnected if Connection is Lost to MQTT, Should do the same with ethernet?
  if (!client.connected())
  { 
    reconnected(client);
  }
  client.loop(); // check MQTT for messages
  readSensors(); // gather data
  client.publish(SensorTopic, PrimaryJson(Smoke).c_str()); // Send MQTT message with Primary Data
  //Send a Json for Every Secondary Read from
  for (int i = 0; i < NumSecondary; i++)
  {
    client.publish(SensorTopic, SecondaryJson(i + 1, DiscreteInputs[i], FloatRegisters[i]).c_str()); 
  }
  delay(5000);
}