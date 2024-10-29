#include <ModbusRTUSlave.h>
#include <SoftwareSerial.h>

// Pins List
#define SoftTX 16 // A2
#define SoftRX 17 // A3
#define LED 2
#define DHT22 4
#define Motion 5
#define Vibration 6
#define DS18B20 7
#define DERE 9

// Defines the ID for the Secondary Board from 1-246
#define ID 1

// Initialize Libaries
SoftwareSerial modbusSerial(SoftRX, SoftTX);
ModbusRTUSlave modbus(modbusSerial, DERE); // Create Modbus Object


//Modbus Data Types
bool DiscreteInputs[4]; 
uint16_t InputRegister[6]; // Temperature: 0-99, Humidity: 100-199, DHT22 Time: 200-299
float *FloatRegisters = (float*)InputRegister; // Usable Address is from 0-99? Temperature: 0-49, Humidity 50-99 



// Sensor Code
void getDHT22() {
  
    // Read DHT22 Sensor
    // return 2 floats?
    FloatRegisters[0] = 123.421;
    FloatRegisters[1] = -25.781;
}
float getDS18B20() {
  // Read DS18B20
  // Return as a float
}
bool getMotion() {
    // Read Motion Sensor
    // return true if motion detected, false otherwise
}
bool getVibration() {
  // Read SW1815P for Vibration
  // returns a bool???? 
}
bool getSmoke() {
  // Read Smoke Sensor
  // Returns a Bool
}
bool getWaterLeaks() {
  // Read WaterLeaks
  // Returns Bool?
}
void setup() {
    //Initialize Pins
    pinMode(LED, OUTPUT);
    pinMode(DHT22, OUTPUT); //probably Not Needed
    pinMode(Motion, OUTPUT); //probably Not Needed
    pinMode(Vibration, INPUT); //?? idk if this right
    pinMode(DS18B20, OUTPUT); //probably Not Needed

    // Initialize Modbus Data Types
    modbus.configureDiscreteInputs(DiscreteInputs, 4);
    modbus.configureInputRegisters(InputRegister, 6);
             
    //Initialize Modbus and Serial Terminal
    modbus.begin(ID, 9600); 
    modbusSerial.begin(9600);
    Serial.begin(9600); // Debug only

    Serial.println(FloatRegisters[0]);
    Serial.println(FloatRegisters[1]);
}

void loop() {
    
    getDHT22();
    getDS18B20();
    getMotion();
    getVibration();
    getSmoke();
    getWaterLeaks();
    
    if (Serial.available() != 0) { // Only Let it poll when something has been Sent Via Uart
        modbus.poll();          
    }
    delay(500);

    Serial.println(FloatRegisters[0]);
    Serial.println(FloatRegisters[1]);
}