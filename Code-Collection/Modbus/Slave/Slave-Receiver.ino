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

bool coils[1]; // Creating an array where the Coils can go | Read & Write Only Bools

void setup()
{
    pinMode(LED, OUTPUT);

    modbus.configureCoils(coils, 1); // Says where The Coils can go and how many Value is allowed
    modbus.begin(ID, 9600);          // ID | Baud Rate
    Serial.begin(9600);              // For Debuging
}

void loop()
{
    if (Serial.available() != 0) // Check if There been any Request
    {
        Serial.println("LED Change"); // Debugging Line
        modbus.poll();                // Check and act on the request from the Master

        digitalWrite(LED, coils[0]); // Changes LED to Match with new Message
    }

    delay(500);
}