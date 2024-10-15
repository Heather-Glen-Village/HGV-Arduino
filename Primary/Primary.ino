#include <ModbusRTUMaster.h>

// Pins List
#define DERE 9
#define LED 2

// Initialize Library
//SoftwareSerial modbusSerial(SoftRX, SoftTX);
ModbusRTUMaster modbus(Serial, DERE); // Create Modbus Object with port for RS485

uint16_t buffer[1]; // Buffer for Modbus Registers

void setup()
{
  pinMode(LED, OUTPUT);

  modbus.begin(9600);
  Serial.begin(9600); // For Debuging
}

void loop()
{
  Serial.println(modbus.readInputRegisters(1, 4, buffer, 1));
  Serial.println("");
  Serial.println(buffer[0]);
  Serial.println("");

  delay(2000);
}