#include <ModbusRTUSlave.h>

// Pins List
// #define SoftTX 14 // Phyical TX 0
// #define SoftRX 15 // Phyical RX 1
#define DERE 9
#define LED 2

// Defines the ID for the Secondary Board from 1-246
#define ID 1

// Initialize Library
ModbusRTUSlave modbus(Serial, DERE); // Create Modbus Object

uint16_t inputRegisters[1]; // Creating an array where the Coils can go | Read & Write Only Bools

void setup()
{
  pinMode(LED, OUTPUT);

  modbus.configureInputRegisters(inputRegisters, 1);
  modbus.begin(ID, 9600);          // ID | Baud Rate
  Serial.begin(9600);              // For Debuging
  inputRegisters[0] = random(0, 65536);
  Serial.println(inputRegisters[0]);
}

void loop()
{
  if (Serial.available() != 0) // Check if There been any Request
  {
    modbus.poll();// Check and act on the request from the Master
    
    inputRegisters[0] = random(0, 65536);
    Serial.print("Changed to: "); // Debugging Line
    Serial.println(inputRegisters[0]);
  }

  delay(500);
}