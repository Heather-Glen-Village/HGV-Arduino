/*
  Secondary Sensors Sender

  The Skectch Made for Secondarys that collect Data from Sensors and Send them to the Priamry to be send to other locations.

  Pin List
    - D0 RX
    - D1 TX
    - D2 LED
    - D3 
    - D4 
    - D5 
    - D6 
    - D7 
    - D8 
    - D9 
    - D10 
    - D11 
    - D12 
    - D13 

  Created on November 11, 2024
  By Zachary Schultz

*/

//Creating Modbus Connection
#include <ModbusRTUSlave.h>
ModbusRTUSlave modbus(Serial); // No DERE Pins Used

// Initializing Pins
#define LED 2

// Modbus Settingss

#define ID 2

#define CoilColumns 1 
#define DIColumns 5 // Amount of Sensors Using Discrete Inputs
#define IRColumns 6 // Number of Input Register Column so Amount of Float Sensors Needed *2

//Modbus Arrays

bool Coils[CoilColumns];

bool discreteInputs[DIColumns]= {0,1,0,1,0};
// 0=Motion, 1=Water?, 2=... 
uint16_t InputRegister[IRColumns] = {1.22,2.22,3.22};
// 0-1=Temperature
float *FloatRegisters = (float*)InputRegister; // Turns an array of uint16 into floats by taking array in pairs
// 0=Tempature

void setup(){
  modbus.configureCoils(Coils,CoilColumns);
  modbus.configureDiscreteInputs(discreteInputs,DIColumns);
  //modbus.configureHoldingRegisters();
  modbus.configureInputRegisters(InputRegister,IRColumns);

  Serial.begin(9600);
  modbus.begin(ID, 9600);
}

void loop() {
  if (Serial.available() > 0) { //want to test if this isn't need anymore but that a later plan
    modbus.poll(); // Checks for changes
    if (Coils[0] == 1) {
      Coils[0] = 0;
      digitalWrite(LED, !digitalRead(LED));
    }
  }
}