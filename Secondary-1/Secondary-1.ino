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

Coil Address Index
 - (0) Command to Read Sensors

Discrete Inputs Address Index 
 - ()

Input Register Address Index (InputRegister)[FloatRegister]
 - (0-5): Placeholder Datetime Data (Could be remove or add depending on speed of modbus)
 - (6-9)[4-5] DS18B20 Temperature and Humidity
 - (10-13)[6-7] Temperature and Humidity from DHT22



  Created on November 11, 2024
  By Zachary Schultz

*/

// Initializing libraries
#include <ModbusRTUSlave.h>
//Needed for .h Files
#include <OneWire.h>
#include <DallasTemperature.h>

//Importing .h files
#include "conf.h"
#include "DS18B20_Sensor.h"

//Modbus Arrays
bool Coils[CoilAddress];
bool DiscreteInputs[DIAddress];
uint16_t HoldingRegister[HRAddress];
uint16_t InputRegister[IRAddress];
float *FloatRegister = (float*)InputRegister; // Turns an array of uint16 into floats by taking array in pairs
uint16_t LastHolding = HoldingRegister[0];

// Creating Modbus Connection
ModbusRTUSlave modbus(RS485Serial); // No DERE Pins Used

void setup(){
  modbus.configureCoils(Coils,CoilAddress);
  modbus.configureDiscreteInputs(DiscreteInputs,DIAddress);
  modbus.configureHoldingRegisters(HoldingRegister,HRAddress);
  modbus.configureInputRegisters(InputRegister,IRAddress);

  Serial.begin(baud);
  modbus.begin(ID, baud);

  initializeDS18B20();

  Serial.println("Secondary Board Sketch");
  Serial.print("Board ID: "); 
  Serial.println(ID);
  delay(1000);
}

void loop() {    
  modbus.poll(); // Checks for changes
  if (Coils[0] == 1) { // Read Data Only When Primary Tells it To
    FloatRegister[0] = DS18B20_Temp();
    Coils[0] = 0;
  }
}