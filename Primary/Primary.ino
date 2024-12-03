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

//Importing .h files
#include "./errorcheck.h"
#include "./conf.h"

//EthernetClient client; //IDK What this Does or if it needed Probably Later

//Modbus Arrays
// bool Coils[NumSecondary][CoilAddress];
bool discreteInputs[NumSecondary][DIAddress];
uint16_t HoldingRegisters[NumSecondary][HRAddress];
uint16_t InputRegister[NumSecondary][IRAddress];
float (*FloatRegisters)[IRAddress] = (float(*)[IRAddress])InputRegister; // Turns an array of uint16 into floats by taking array in pairs

// Creating Modbus Connection
ModbusRTUMaster modbus(RS485Serial); // No DERE Pins Used


void setup() {
  Serial.begin(baud); // Could be remove after everything is wokring? It might only be needed for Debuging
  modbus.begin(baud);
  Serial.println("Primary Board Sketch");
  delay(1000);

  //check if We can get internet connection Just for testing will want a static IP Later
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

void loop(){
  Serial.println();
  Serial.println("----------------------------------------------------------------");
  for (int i = 0; i < NumSecondary; i++) {
    errorCheck(modbus.readDiscreteInputs(i+1,0,discreteInputs[i],DIAddress));
    delay(100);
  }
  Serial.println();
  Serial.println("-----Discrete Input-----");
  Serial.println(String(discreteInputs[0][0])+String(discreteInputs[0][1])+String(discreteInputs[0][2])+String(discreteInputs[0][3])+String(discreteInputs[0][4]));
  Serial.println(String(discreteInputs[1][0])+String(discreteInputs[1][1])+String(discreteInputs[1][2])+String(discreteInputs[1][3])+String(discreteInputs[1][4]));
  Serial.println(String(discreteInputs[2][0])+String(discreteInputs[2][1])+String(discreteInputs[2][2])+String(discreteInputs[2][3])+String(discreteInputs[2][4]));
  Serial.println(String(discreteInputs[3][0])+String(discreteInputs[3][1])+String(discreteInputs[3][2])+String(discreteInputs[3][3])+String(discreteInputs[3][4]));
  delay(5000);
  

  for (int i = 0; i < NumSecondary; i++) {
    errorCheck(modbus.readInputRegisters(i+1,0,InputRegister[i],IRAddress));
    delay(100);
  }
  Serial.println();
  Serial.println("-----Input Register Raw-----");
  Serial.println(String(InputRegister[0][0])+String(InputRegister[0][1])+String(InputRegister[0][2])+String(InputRegister[0][3])+String(InputRegister[0][4])+String(InputRegister[0][5]));
  Serial.println(String(InputRegister[1][0])+String(InputRegister[1][1])+String(InputRegister[1][2])+String(InputRegister[1][3])+String(InputRegister[1][4])+String(InputRegister[1][5]));
  Serial.println(String(InputRegister[2][0])+String(InputRegister[2][1])+String(InputRegister[2][2])+String(InputRegister[2][3])+String(InputRegister[2][4])+String(InputRegister[2][5]));
  Serial.println(String(InputRegister[3][0])+String(InputRegister[3][1])+String(InputRegister[3][2])+String(InputRegister[3][3])+String(InputRegister[3][4])+String(InputRegister[3][5]));
  Serial.println("-----Input Register Float-----");
  Serial.println(String(FloatRegisters[0][0])+String(FloatRegisters[0][1])+String(FloatRegisters[0][2]));
  Serial.println(String(FloatRegisters[1][0])+String(FloatRegisters[1][1])+String(FloatRegisters[1][2]));
  Serial.println(String(FloatRegisters[2][0])+String(FloatRegisters[2][1])+String(FloatRegisters[2][2]));
  Serial.println(String(FloatRegisters[3][0])+String(FloatRegisters[3][1])+String(FloatRegisters[3][2]));
  delay(5000);
  Serial.println("Writing to Coils");
  errorCheck(modbus.writeSingleCoil(0,0,1));
  delay(100);
  Serial.println("Writing to Holding Register");
  errorCheck(modbus.writeSingleHoldingRegister(0,0,175));
  delay(1000);
  for (int i = 0; i < NumSecondary; i++) {
    errorCheck(modbus.readHoldingRegisters(i+1,0,HoldingRegisters[i],HRAddress));
    delay(100);
  }
  Serial.println(HoldingRegisters[0][0]);
  Serial.println(HoldingRegisters[1][0]);
  Serial.println(HoldingRegisters[2][0]);
  Serial.println(HoldingRegisters[3][0]);
  delay(3000);


}