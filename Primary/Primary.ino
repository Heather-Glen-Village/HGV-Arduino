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
#include <ArduinoRS485.h>
#include <ArduinoModbus.h>
#include <SPI.h>
#include <Ethernet.h>

// Initializing pins

// Game plan is to Get Priamry to try and get a random Input Register for every device then try a call for all data  


#define LED 2

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF 
};
EthernetClient client;

uint16_t PreFloat[2];
float *FloatRegisters = (float*)PreFloat;

//Arrays used to store Modbus information and Convert them into useful form?
//We May not need to convert in Primary or at all?
//3 test need to be done. first talking to all board using modbus 2nd trying a cast command and 3rd sending something such as a string or float
// CHANGE OF PLAN IDC I'm USING OLD LIB THEY ARE NICE AND I KNOW HOW TO USE THEM sorta?
// maybe try to get something working here then see if I like it or not
// prob still use it for TCP tho


void setup() {
  Serial.begin(9600);
  Serial.println("Primary Board Sketch");
  delay(1000);


  // start the Modbus RTU client
  RS485.setPins(1,0,-1);
  if (!ModbusRTUClient.begin(9600)) {
    Serial.println("Failed to start Modbus RTU Client!");
    while (1);
  }

    //check if We can get internet connection Just for testing will want a static IP Later
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    } else if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // no point in carrying on, so do nothing forevermore:
      while(true){
        Serial.println("Board is most likely not the Priamry Board");
        delay(1000);
      }    
  } else {
    Serial.println(Ethernet.localIP());
    Serial.println("This is a Priamry Board");
  }
}

void loop() {
  //test if we can connected to each board and read some data
  for (int i = 1; i < 4; i++) {
    auto inputRegister = ModbusRTUClient.inputRegisterRead(i, 0);
    if (!inputRegister) {
      Serial.print("Failed to Read IR 1! ");
      Serial.println(ModbusRTUClient.lastError());
    } else {
      Serial.print(inputRegister);
    }
    delay(500);
  }

  // testing what happens when we try to read id 0 with more then 1 board problly breaks
    uint16_t inputRegister = ModbusRTUClient.inputRegisterRead(0);
    if (!inputRegister) {
      Serial.print("Failed to Read IR! ");
      Serial.println(ModbusRTUClient.lastError());
    } else {
      Serial.print(inputRegister);
    }
    delay(500);

      // Testing if it possible to Write to all the Secondarty at onces
    if (!ModbusRTUClient.coilWrite(0,1)) {
      Serial.print("Failed to Read Coil! ");
      Serial.println(ModbusRTUClient.lastError());
    } 

    delay(2000);
    if (!ModbusRTUClient.coilWrite(0,0)) {
      Serial.print("Failed to Read Coil! ");
      Serial.println(ModbusRTUClient.lastError());
    } 

    delay(500);

    //test if point and float still work

    for (int i = 0; i < 2; i++) {
    PreFloat[i] = ModbusRTUClient.inputRegisterRead(1, i+1);
    if (!PreFloat[i]) {
      Serial.print("Failed to Read IR! ");
      Serial.println(ModbusRTUClient.lastError());
    } else {
      Serial.print(PreFloat[i]);
    }
    delay(500);
  }
  Serial.println(FloatRegisters[0]);
}