#include <ModbusRTUSlave.h>
#include <time.h>





// Pins List
// #define SoftTX 14 // Phyical TX 0
// #define SoftRX 15 // Phyical RX 1
#define DERE 9
#define LED 2

// Defines the ID for the Secondary Board from 1-246
#define ID 2

// Initialize Libaries
ModbusRTUSlave modbus(Serial, DERE); // Create Modbus Object


//Modbus Data Types
bool coils[1]; 


// Sensor Code
float getTemperature() {
    // Read Temperature Sensor
    // return as a int? 
}
void setup()
{
    //Initialize Pins
    pinMode(LED, OUTPUT);

    // Initialize Modbus
    modbus.configureCoils(coils, 1); // Says where The Coils can go and how many Value is allowed
    modbus.begin(ID, 9600);          // ID | Baud Rate
    //Initialize Serial
    Serial.begin(9600);              // For Debuging
}

void loop()
{
    if (Serial.available() != 0) // Check if There been any Request
    {
        modbus.poll();           //act on the request from the Master
    }
    time_t t = now();
    Serial.println(t)
    delay(500); // Remove or lower at some point?
}