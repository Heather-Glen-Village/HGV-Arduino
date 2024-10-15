#include <SoftwareSerial.h>
#include <ModbusRTUMaster.h>

// Pins List
#define SoftTX 14 // Phyical TX 0
#define SoftRX 15 // Phyical RX 1
#define DERE 9
#define LED 2

// Initialize Library
//SoftwareSerial modbusSerial(SoftRX, SoftTX);
ModbusRTUMaster modbus(Serial, DERE); // Create Modbus Object with port for RS485

uint16_t buffer[2]; // Buffer for Modbus Registers

void setup()
{
  pinMode(LED, OUTPUT);

  modbus.begin(9600);
  Serial.begin(9600); // For Debuging
}

void loop()
{
  Serial.println("----------------------------------------------------------------");
  Serial.println(modbus.readInputRegisters(1, 0, buffer, 1));
  Serial.println("");
  Serial.print("Buffer 1: ");
  Serial.println(buffer[0]);
  Serial.print("Buffer 2: ");
  Serial.println(buffer[1]);

  delay(2000);
}