/*
  Primary Arduino Control

  This sketch is the Code That lets the Priamry Act as a RTC Master, TCP Server, and Control All Sensor and System Connected

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

//Importing .h files
#include "conf.h"
#include "errorcheck.h"
#include "mqtt.h"

ModbusRTUMaster modbus(RS485Serial); // No DERE Pins Used
EthernetClient ethClient;
PubSubClient client(server, port, callback, ethClient);

//Modbus Arrays
bool Coils[NumSecondary][CoilAddress];
bool discreteInputs[NumSecondary][DIAddress];
uint16_t HoldingRegisters[NumSecondary][HRAddress];
uint16_t InputRegisters[NumSecondary][IRAddress];
float (*FloatRegisters)[IRAddress/2] = (float(*)[IRAddress/2])InputRegisters; // Turns an array of uint16 into floats by taking array in pairs
bool Smoke = 1;

void readSensors() {
  Serial.println("Telling Secondarys to Read Sensors");
  errorCheck(modbus.writeSingleCoil(0,0,1)); //Tells All Secondary to Read Sensors

  //NEED to Rethink how Smoke Is being Sent Smoke
  // Maybe have A Json just for Primary Data but Idk what else to put there
  // another Opition is to Put in only in the lastJson file or all of them both would have the same effect but one would be faster ig
  Smoke = 1;

  delay(5000); //wait for Sensors to Read and Serial to Clear (COULD BE SHORTEN/REMOVED IF NEEDED)

  //Read all sensor data from secondary
  for (int i = 0; i < NumSecondary; i++) { 
    errorCheck(modbus.readDiscreteInputs(i+1,0,discreteInputs[i],DIAddress));
    delay(100);
  }
  for (int i = 0; i < NumSecondary; i++) {
    errorCheck(modbus.readInputRegisters(i+1,0,InputRegisters[i],IRAddress));
    delay(100);
  }
}

void printdata() {
  Serial.println("-----Discrete Input-----");
  for (int i = 0; i < NumSecondary; i++)
  {
    for (int z = 0; z < DIAddress; z++)
    {
      Serial.print(discreteInputs[i][z]);
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
    for (int z = 0; z < IRAddress/2; z++)
    {
      Serial.print(FloatRegisters[i][z]);
      Serial.print(",");
      delay(100);
    }
    Serial.println();
  }
}

// ----------Basic Setup and Loop Start Here ----------
void setup() {
  Serial.begin(baud);
  modbus.begin(baud);
  pinMode(LED, OUTPUT);
  Serial.println("Primary Board Sketch");
  EthConnect();
  delay(1000);
  }

void loop() {
  if (!client.connected()) { // Reconnected if Connection is Lost, Should do the same with ethernet?
    reconnected(client);
  }
  client.loop();
  readSensors();
  sendData(client, discreteInputs, FloatRegisters, Smoke);
  delay(5000);
}