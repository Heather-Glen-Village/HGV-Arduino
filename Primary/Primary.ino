#include <ModbusRTUMaster.h>

// Pins List

//#define TX  0
//#define RX  1
#define DERE  9
#define LED   2

ModbusRTUMaster modbus(Serial, DERE); // Create Modbus Object with port for RS485

bool SlaveLED = 1; // Enable

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, SlaveLED);
  //modbus.setTimeout(500);
  modbus.begin(9600); // Baud Rate  | Config?
}

void loop() {
  if (modbus.writeSingleCoil(1, 0, SlaveLED) == 0) {
    SlaveLED = !SlaveLED;
  }
  digitalWrite(LED, SlaveLED);
  delay(2000);
}