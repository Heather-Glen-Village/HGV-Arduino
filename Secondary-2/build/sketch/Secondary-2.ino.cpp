#include <Arduino.h>
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
#include <SoftwareSerial.h>
#include <ModbusRTUSlave.h>
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

bool coils[1] = {1};
uint16_t InputRegisters[2];
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

#line 38 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
void setup();
#line 48 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
void loop();
#line 38 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
void setup()
{
  pinMode(LED, OUTPUT);

  modbus.configureCoils(coils, 1);
  modbus.configureInputRegisters(InputRegisters, 2);
  modbus.begin(ID, 19200);          // ID | Baud Rate
  Serial.begin(9600);              // For Debuging
}

void loop() {
modbus.poll();
    if (coils[0] == 1) {
        coils[0] = 0;
        if (x == 99) {
            x = 0;
        }
        else {
            x++;
        }
        FloatRegisters[0] = floatArray[x];
        Serial.println();
        Serial.println("----------------------------------------------------------------");
        Serial.print("InputRegisters 1: "); Serial.println(InputRegisters[0]);
        Serial.print("InputRegisters 2: "); Serial.println(InputRegisters[1]);
        Serial.print("Float Registers 1: "); Serial.println(FloatRegisters[0]);
    }
}
