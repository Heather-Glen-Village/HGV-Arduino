#include <ModbusRTUMaster.h>

// Pins List
#define DERE 9
#define LED 2

// Initialize Library
//SoftwareSerial modbusSerial(SoftRX, SoftTX);
ModbusRTUMaster modbus(Serial, DERE); // Create Modbus Object with port for RS485

bool coils[2] = {0,0}; // Buffer for Modbus Registers
bool on[2] = {1,1};

void setup()
{
  pinMode(LED, OUTPUT);

  modbus.begin(9600);
  Serial.begin(9600); // For Debuging
  delay(10000); //
}

void loop() {
if (coils[0] == 0 && coils[1] == 0) {
  modbus.writeMultipleCoils(1, 0, on, 2);
  Serial.println("ON!");
}
delay(5000);

}