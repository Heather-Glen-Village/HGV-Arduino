/*
  Secondary Sensors Sender

  The Skectch Made for Secondarys that collect Data from Sensors and Send them to the Priamry to be send to other locations.

  Pin List
    - D0 RX
    - D1 TX
    - D2 LED
    - D4 AM2302 Heat/DHT22
    - D5 SR-HC 50x Motion
    - D6 SW-1815P Vibration Sensor
    - D7 DS18B20 Heat
    - D14/A0 Water Leak Set 1 (Digital)
    - D15/A1 Water Leak Set 2 (Digital)
    - D18/A6 Water Leak Set 1 (Analog)
    - D19/A7 Water Leak Set 2 (Analog)

  Created on November 11, 2024
  By Zachary Schultz

*/

//Creating Modbus Connection
#include <ModbusRTUSlave.h>
ModbusRTUSlave modbus(Serial); // No DERE Pins Used

// Initializing Pins
#define LED 2

// Modbus Settingss

#define ID 4

#define CoilColumns 1 
#define DIColumns 5 // Amount of Sensors Using Discrete Inputs
#define HRColumns 1
#define IRColumns 6 // Number of Input Register Column so Amount of Float Sensors Needed *2

//Modbus Arrays

bool Coils[CoilColumns];

bool DiscreteInputs[DIColumns] = {1,0,1,0,0}; 
// 0=Motion, 1=Water?, 2=... 
uint16_t HoldingRegister[HRColumns];
uint16_t InputRegister[IRColumns] = {1.44,2.44,3.44};
// 0-1=Temperature
float *FloatRegisters = (float*)InputRegister; // Turns an array of uint16 into floats by taking array in pairs
// 0=Tempature

void setup(){
  modbus.configureCoils(Coils,CoilColumns);
  modbus.configureDiscreteInputs(DiscreteInputs,DIColumns);
  modbus.configureHoldingRegisters(HoldingRegister,HRColumns);
  modbus.configureInputRegisters(InputRegister,IRColumns);

  Serial.begin(9600);
  modbus.begin(ID, 9600);

  Serial.println("Secondary Board Sketch");
  Serial.print("Board ID: "); 
  Serial.println(ID);
  delay(1000);
}

void loop() {
  if (Serial.available() > 0) { //want to test if this isn't need anymore but that a later plan
    modbus.poll(); // Checks for changes
    if (Coils[0] == 1) {
      Coils[0] = 0;
      digitalWrite(LED, !digitalRead(LED));
    }
    Serial.print("Holding Register: ");
    Serial.println(HoldingRegister[0]);
  }
}