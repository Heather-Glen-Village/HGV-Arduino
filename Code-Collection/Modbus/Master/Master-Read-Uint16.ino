#include <SoftwareSerial.h>
#include <ModbusRTUMaster.h>

// Pins List
#define SoftDI 14 // A0
#define SoftRO 15 // A1
#define LED 2
#define DHT22 4
#define Motion 5
#define Vibration 6
#define DS18B20 7
#define DERE 9

// Defines the ID for the Secondary Board from 1-246
#define ID 1

// Initialize Libaries
SoftwareSerial modbusSerial(SoftRO, SoftDI); // RX TX
ModbusRTUMaster modbus(modbusSerial, DERE); // Create Modbus Object

bool coils[1] = {1};
uint16_t InputRegisters[1];


void setup() {
  modbus.begin(9600);
  Serial.begin(9600); // For Debuging
  delay(5000);        // For Debuging
}

void loop() {
Serial.println(modbus.writeSingleCoil(1,0,1));
delay(3000);
Serial.println(modbus.readInputRegisters(1, 0, InputRegisters,1));
Serial.print("InputRegisters: "); Serial.println(InputRegisters[0]);
delay(1000);
}