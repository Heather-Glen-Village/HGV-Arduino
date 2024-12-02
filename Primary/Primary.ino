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

  Created on November 11, 2024
  By Zachary Schultz

*/
// Initializing libraries

#include <SPI.h>
#include <Ethernet.h>
#include <ModbusRTUMaster.h>
#include <PubSubClient.h>

// Imports from other Files
#include "./errorcheck.h"

// Initializing Values

#define LED 2

#define NumSecondary 4
#define DIColumns 5 // Amount of Sensors Using Discrete Inputs
#define IRColumns 6 // Number of Input Register Column so Amount of Float Sensors Needed *2

//Ethernet Setup
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF 
};
EthernetClient client;
//Modbus Arrays

bool discreteInputs[NumSecondary][DIColumns];
// 0=Motion, 1=Water?, 2=... 
uint16_t InputRegister[NumSecondary][IRColumns];
// 0-1=Temperature
float (*FloatRegisters)[IRColumns] = (float(*)[IRColumns])InputRegister; // Turns an array of uint16 into floats by taking array in pairs
// 0=Tempature




// Creating Modbus Connection
ModbusRTUMaster modbus(Serial); // No DERE Pins Used


void setup() {
  Serial.begin(9600); // Could be remove after everything is wokring? It might only be needed for Debuging
  modbus.begin(9600);
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
      while(true) { // no point in carrying on, so do nothing forevermore:
        Serial.println("Board is most likely not the Priamry Board");
        delay(1000);
      }    
  } 
  else {
    Serial.println(Ethernet.localIP());
    Serial.println("This is a Priamry Board");
  }
}

void loop(){
  for (int i = 0; i < NumSecondary; i++) {
    errorCheck(modbus.readDiscreteInputs(i+1,0,discreteInputs[i],DIColumns));
    Serial.println(discreteInputs[i][0]);
    delay(100);
  }

  for (int i = 0; i < NumSecondary; i++) {
    errorCheck(modbus.readInputRegisters(i+1,0,InputRegister[i],IRColumns));
    Serial.println(InputRegister[i][0]);
    Serial.println(FloatRegisters[i][0]);
    delay(100);
  }
  errorCheck(modbus.writeSingleCoil(0,0,1));
  delay(3000);
}