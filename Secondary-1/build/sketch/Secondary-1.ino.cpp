#include <Arduino.h>
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
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

bool coils[1] = {1};
uint16_t InputRegisters[4];
float *FloatRegisters = (float*)InputRegisters; // Usable Address is from 0-99? Temperature: 0-49, Humidity 50-99 

float floatArray[100] = {
    12.34, 45.67, 89.12, 34.56, 78.90, 23.45, 67.89, 12.34, 56.78, 90.12,
    34.56, 78.90, 23.45, 67.89, 12.34, 56.78, 90.12, 34.56, 78.90, 23.45,
    67.89, 12.34, 56.78, 90.12, 34.56, 78.90, 23.45, 67.89, 12.34, 56.78,
    90.12, 34.56, 78.90, 23.45, 67.89, 12.34, 56.78, 90.12, 34.56, 78.90,
    23.45, 67.89, 12.34, 56.78, 90.12, 34.56, 78.90, 23.45, 67.89, 12.34,
    56.78, 90.12, 34.56, 78.90, 23.45, 67.89, 12.34, 56.78, 90.12, 34.56,
    78.90, 23.45, 67.89, 12.34, 56.78, 90.12, 34.56, 78.90, 23.45, 67.89,
    12.34, 56.78, 90.12, 34.56, 78.90, 23.45, 67.89, 12.34, 56.78, 90.12,
    34.56, 78.90, 23.45, 67.89, 12.34, 56.78, 90.12, 34.56, 78.90, 23.45,
    67.89, 12.34, 56.78, 90.12, 34.56, 78.90, 23.45, 67.89, 12.34, 56.78
};
int16_t x = -1;

#line 33 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void setup();
#line 43 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void loop();
#line 50 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void newFloat();
#line 33 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void setup()
{
  pinMode(LED, OUTPUT);

  modbus.configureCoils(coils, 1);
  modbus.configureInputRegisters(InputRegisters, 4);
  modbus.begin(ID, 19200);          // ID | Baud Rate
  Serial.begin(9600);              // For Debuging
}

void loop() {
    if (Serial.available() != 0) {
        newFloat()
        modbus.poll();
    }
    delay(100);
}
void newFloat() {

    if (coils[0] == 1) {
        coils[0] = 0;
        if (x == 99) {
            x = 0;
        }
        else {
            x++;
        }
        FloatRegisters[0] = floatArray[x];
        FloatRegisters[1] = floatArray[x + 1];
        Serial.println();
        Serial.println("----------------------------------------------------------------");
        Serial.print("InputRegisters 1: "); Serial.println(InputRegisters[0]);
        Serial.print("InputRegisters 2: "); Serial.println(InputRegisters[1]);
        Serial.print("Float Registers 1: "); Serial.println(FloatRegisters[0]);
        Serial.println();
        Serial.print("InputRegisters 3: "); Serial.println(InputRegisters[2]);
        Serial.print("InputRegisters 4: "); Serial.println(InputRegisters[3]);
        Serial.print("Float Registers 2: "); Serial.println(FloatRegisters[1]);
    }
}
