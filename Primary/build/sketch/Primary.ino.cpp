#include <Arduino.h>
#line 1 "D:\\Github\\HGV\\rems006-Arduino\\Primary\\Primary.ino"


/*
  Primary Arduino Control

  This sketch is the Code That lets the Priamry Act as a RTC Master, TCP Server, and Control All Sensor and System Connected

  Pin List
    - D2 LED
    - D3 Smoke
    - D4 Heat On
    - D5 Water Off
    - D6 Power Off
    - D7 Cool On
    - D8 Eth-Int?
    - D9 Dere Power (Unused)
    - D10 Eth-CSN
    - D11 Eth-MOSI
    - D12 Eth-MISO
    - D13 Eth-SCK
    - D16(A2) SoftRX
    - D17(A3) SoftTX

  Created on November 20, 2024
  By Zachary Schultz

*/
// Initializing libraries
#include <SoftwareSerial.h>
#include <ArduinoRS485.h>
#include <ArduinoModbus.h>
#include <SPI.h>
#include <Ethernet.h>
// #include <ModbusRTUServer.h>
// #include <ModbusServer.h>
// #include <ModbusTCPServer.h>

// Initializing pins

#define rxPin 16 // A2
#define txPin 17 // A3
#define LED 2
// Initializing the uses of SoftwareSerial
// SoftwareSerial modbusSerial(rxPin, txPin); // RX TX

#line 46 "D:\\Github\\HGV\\rems006-Arduino\\Primary\\Primary.ino"
void setup();
#line 55 "D:\\Github\\HGV\\rems006-Arduino\\Primary\\Primary.ino"
void loop();
#line 46 "D:\\Github\\HGV\\rems006-Arduino\\Primary\\Primary.ino"
void setup()
{
  Serial.begin(9600);               // for Debug
  RS485.setPins(txPin, rxPin, LED); // Board don't Use RE pin so set it to LED so it lights up while Sending
  if (!ModbusRTUServer.begin(1, 9600))
  {
  }
}

void loop()
{
}

