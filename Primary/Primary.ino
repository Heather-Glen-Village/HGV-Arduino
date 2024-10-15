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
  coils[0] = on[0];
  coils[1] = on[1];
  Serial.println(coils[0]);
  Serial.println(coils[1]);
  Serial.println("ON!");
}
else if (coils[0] == 1 && coils[1] == 1) {
  modbus.readCoils(1,0, coils, 2);
  Serial.println(coils[0]);
  Serial.println(coils[1]);
  Serial.println("OFF!");
  }
delay(5000);

}