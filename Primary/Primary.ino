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
    Coils:
      Currently Just for Testing
    discreteInputs:
      - 0=Motion
      - 1=Water?
      - 2=...
    Holding Register:
      Currently Just for Testing
    Input Register:
    - 0-1=Temperature
    - 2-3=Humidity

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
PubSubClient client(server, 1883, callback, ethClient);

//Modbus Arrays
bool Coils[NumSecondary][CoilAddress];
bool discreteInputs[NumSecondary][DIAddress];
uint16_t HoldingRegisters[NumSecondary][HRAddress];
uint16_t InputRegister[NumSecondary][IRAddress];
float (*FloatRegisters)[IRAddress/2] = (float(*)[IRAddress/2])InputRegister; // Turns an array of uint16 into floats by taking array in pairs

void readSensors() {
  //Run RTC Comand to save when Signel Goes out to Read
  errorCheck(modbus.writeSingleCoil(0,0,1)); //Tells All Secondary to Read Sensors

  //Check any Sensors on Primary Such as Water and Smoke
  delay(5000); //wait for Sensors to Read and Serial to Clear (COULD BE SHORTEN/REMOVED IF NEEDED)

  //Read all sensor data from secondary
  for (int i = 0; i < NumSecondary; i++) { 
    errorCheck(modbus.readDiscreteInputs(i+1,0,discreteInputs[i],DIAddress));
    delay(100);
  }
  for (int i = 0; i < NumSecondary; i++) {
    errorCheck(modbus.readInputRegisters(i+1,0,InputRegister[i],IRAddress));
    delay(100);
  }
}

// ----------Basic Setup and Loop Start Here ----------
void setup() {
  Serial.begin(baud);
  modbus.begin(baud);
  pinMode(LED, OUTPUT);
  Serial.println("Primary Board Sketch");
  
  delay(1000);
  EthConnect();
  }

void loop(){
  if (!client.connected()) { // Reconnected if Connection is Lost, Should do the same with ethernet?
    reconnected(client);
  }
  client.loop();
  readSensors();
  sendData(client, discreteInputs, FloatRegisters);
  delay(5000);
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
      Serial.print(InputRegister[i][z]);
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