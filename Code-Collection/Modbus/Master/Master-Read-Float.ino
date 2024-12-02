#include <ModbusRTUMaster.h>

// Pins List
#define DERE 9
#define LED 2

// Initialize Library
//SoftwareSerial modbusSerial(SoftRX, SoftTX);
ModbusRTUMaster modbus(Serial, DERE); // Create Modbus Object with port for RS485

uint16_t InputRegisters[2];
float *FloatRegisters = (float*)InputRegisters; // Usable Address is from 0-99? Temperature: 0-49, Humidity 50-99 


void setup() {
  pinMode(LED, OUTPUT);

  modbus.begin(19200);
  Serial.begin(9600); // For Debuging
  delay(10000); //
}

void loop() {
modbus.writeSingleCoil(1,0,1);
delay(3000);
modbus.readInputRegisters(1, 0, InputRegisters,2);
Serial.println();
Serial.println("----------------------------------------------------------------");
Serial.print("InputRegisters 1: "); Serial.println(InputRegisters[0]);
Serial.print("InputRegisters 2: "); Serial.println(InputRegisters[1]);
Serial.print("Float Registers 1: "); Serial.println(FloatRegisters[0]);
delay(1000);
}