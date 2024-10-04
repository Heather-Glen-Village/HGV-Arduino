#include <SoftwareSerial.h>
//#include <NeoSWSerial.h>
#include <ModbusRTUMaster.h>

// Pins List

#define TX    14 //Phyical TX 0
#define RX    15 //Phyical RX 1
#define DERE  9
#define LED   2
SoftwareSerial modbusSerial(RX, TX);
ModbusRTUMaster modbus(modbusSerial, DERE); // Create Modbus Object with port for RS485


bool SlaveLED = 1; // Enable

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, SlaveLED);
  //modbus.setTimeout(500);
  modbus.begin(9600); // Baud Rate  | Config?
  Serial.begin(9600);
}

void loop() {
  if (modbus.writeSingleCoil(1, 0, SlaveLED) == 0) {
    SlaveLED = !SlaveLED;
  }
  else{
    Serial.println(modbus.getExceptionResponse());
  }
  digitalWrite(LED, SlaveLED);
  delay(2000);
}