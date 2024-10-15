#include <ModbusRTUMaster.h>

// Pins List
#define DERE 9
#define LED 2

// Initialize Library
//SoftwareSerial modbusSerial(SoftRX, SoftTX);
ModbusRTUMaster modbus(Serial, DERE); // Create Modbus Object with port for RS485

bool discreteInput[2]; // Buffer for Modbus Registers

void setup()
{
  pinMode(LED, OUTPUT);

  modbus.begin(9600);
  Serial.begin(9600); // For Debuging
  delay(10000); //
}

void loop() {
modbus.writeSingleCoil(1,0,1);
delay(3000);
modbus.readDiscreteInputs(1,0, discreteInput,2);
Serial.println();
Serial.print("discreteInput 1: "); Serial.println(discreteInput[0]);
Serial.print("discreteInput 2: "); Serial.println(discreteInput[1]);
delay(1000);
}