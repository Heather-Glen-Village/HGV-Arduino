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

bool coils[2]= {0,0};

void setup()
{
  pinMode(LED, OUTPUT);

  modbus.configureCoils(coils, 2);
  modbus.begin(ID, 9600);          // ID | Baud Rate
  Serial.begin(9600);              // For Debuging
}

void loop() {

Serial.println();
Serial.println(coils[0]);
Serial.println(coils[1]);

modbus.poll();
delay(500);
if (coils[0] == 1 && coils[1] == 1){
    Serial.println("----------------------------------------------------------------");
    coils[0] = 0;
    coils[1] = 0;
    }
}