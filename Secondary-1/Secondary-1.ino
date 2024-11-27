

/*
  Secondary Arduino 

  Code to Send Over Sensor Information to the Primary Arduino Using ModbusRTU

  Pin List

  Created on November 11, 2024
  By Zachary Schultz

*/
// Initializing libraries
#include <SoftwareSerial.h>
#include <ArduinoRS485.h>
#include <ArduinoModbus.h>
#include <SPI.h>
#include <Ethernet.h>

// Initializing pins

#define rxPin 16 // A2
#define txPin 17 // A3
#define LED 8
// Initializing the uses of SoftwareSerial
// SoftwareSerial modbusSerial(rxPin, txPin); // RX TX

void setup()
{
  Serial.begin(9600);               // for Debug
  RS485.setPins(txPin, rxPin, LED); // Board don't Use RE pin so set it to LED so it lights up while Sending
  ModbusRTUServer.configureCoils(0, 10);
  ModbusRTUServer.configureHoldingRegisters(0, 10);
  if (!ModbusRTUServer.begin(1, 9600))
  {
  }
}

void loop()
{
}
