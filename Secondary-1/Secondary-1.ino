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

bool coils[1]= {1};
bool discreteInput[2] = {1,0};

void setup()
{
  pinMode(LED, OUTPUT);

  modbus.configureCoils(coils, 1);
  modbus.configureDiscreteInputs(discreteInput, 2);
  modbus.begin(ID, 9600);          // ID | Baud Rate
  Serial.begin(9600);              // For Debuging
}

void loop() {
modbus.poll();
    if (coils[0] == 1) {
        coils[0] = 0;
        discreteInput[0] = !discreteInput[0];
        discreteInput[1] = !discreteInput[1];
        Serial.println();
        Serial.print("discreteInput 1: "); Serial.println(discreteInput[0]);
        Serial.print("discreteInput 2: "); Serial.println(discreteInput[1]);
    }
}