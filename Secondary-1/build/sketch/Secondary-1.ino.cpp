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

  Created on November 11, 2024
  By Zachary Schultz

*/

// Initializing libraries
#include <ModbusRTUSlave.h>
#include <OneWire.h>
#include <DallasTemperature.h>
//Importing .h files
#include "./conf.h"
#

//Modbus Arrays
bool Coils[CoilAddress];
bool DiscreteInputs[DIAddress];
uint16_t HoldingRegister[HRAddress];
uint16_t InputRegister[IRAddress];
float *FloatRegister = (float*)InputRegister; // Turns an array of uint16 into floats by taking array in pairs
uint16_t LastHolding = HoldingRegister[0];

// Creating Modbus Connection
ModbusRTUSlave modbus(RS485Serial); // No DERE Pins Used


//Sensor Setup 
OneWire oneWire(DS18B20_PIN);
DallasTemperature DS18B20(&oneWire);

#line 48 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void setup();
#line 76 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void loop();
#line 48 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void setup(){
  modbus.configureCoils(Coils,CoilAddress);
  modbus.configureDiscreteInputs(DiscreteInputs,DIAddress);
  modbus.configureHoldingRegisters(HoldingRegister,HRAddress);
  modbus.configureInputRegisters(InputRegister,IRAddress);

  Serial.begin(baud);
  modbus.begin(ID, baud);

  Serial.println("Secondary Board Sketch");
  Serial.print("Board ID: "); 
  Serial.println(ID);
  delay(1000);

  //test data
  DiscreteInputs[0] = 0;
  DiscreteInputs[1] = 0;
  DiscreteInputs[2] = 0;
  DiscreteInputs[3] = 0;
  DiscreteInputs[4] = 1;

  FloatRegister[0] = 1.11f;
  FloatRegister[1] = 2.11f;
  FloatRegister[2] = 3.11f;

  
}

void loop() {    
  modbus.poll(); // Checks for changes
  if (Coils[0] == 1) {
    Coils[0] = 0;
    digitalWrite(LED, !digitalRead(LED));
    Serial.println("Coil Changed");
  }
  if (LastHolding = HoldingRegister[0]) {
    Serial.print("Holding Register Changed: ");
    Serial.println(HoldingRegister[0]);
    LastHolding = HoldingRegister[0];
  }
}

