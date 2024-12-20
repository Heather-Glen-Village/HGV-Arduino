#include <Arduino.h>
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
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
 - (0) Motion Sensor
 - (1) Water Leak Sensor
 - (2) Smoke Data (From Primary)
 - (2) Vibration Sensor

Input Register/Float Register Address Index (InputRegister)[FloatRegister]
 - (0-1)[0] Temperature from DS18B20 
 - (2-5)[1-2] Temperature and Humidity from AM2302

  Created on November 11, 2024
  By Zachary Schultz
  Help from Arham Rashad For Sensor Code
*/

// Initializing libraries
#include <ModbusRTUSlave.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>

//Importing .h files
#include "conf.h"
#include "DS18B20_Sensor.h"
#include "AM2302_Sensor.h"

//Modbus Arrays
bool Coils[CoilAddress];
bool DiscreteInputs[DIAddress];
uint16_t HoldingRegister[HRAddress];
uint16_t InputRegister[IRAddress];
float *FloatRegister = (float*)InputRegister; // Turns an array of uint16 into floats by taking array in pairs

// Creating Modbus Connection
ModbusRTUSlave modbus(RS485Serial); // No DERE Pins Used

#line 58 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void readDebug();
#line 69 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void setup();
#line 86 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void loop();
#line 58 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void readDebug() {
      Serial.print("DS18B20 Temperature: ");
      Serial.println(DS18B20_Temp());
      Serial.print("AM2302 Temperature: ");
      Serial.println(AM2302_Temp());
      Serial.print("AM2302 Humidity: ");
      Serial.println(AM2302_Humidity());
      delay(10000);
}


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
    FloatRegister[1] = AM2302_Temp();
    FloatRegister[2] = AM2302_Humidity();

    DiscreteInputs[0] = 1;
    DiscreteInputs[1] = 1;
    DiscreteInputs[2] = 1;
    DiscreteInputs[3] = 0; //Always Zero As Primary Fills This in

    Coils[0] = 0; // Pervent Looping More then 1 Time
  } 
  // else {
  //   readDebug();
  // }
  // delay(1000);
}
