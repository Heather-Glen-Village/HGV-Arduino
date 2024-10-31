#include <SoftwareSerial.h>
#include <ModbusRTUSlave.h>

// Pins List
#define SoftDI 16 // A2
#define SoftRO 17 // A3
#define LED 2
#define DHT22 4
#define Motion 5
#define Vibration 6
#define DS18B20 7
#define DERE 9

// Defines the ID for the Secondary Board from 1-246
#define ID 1

// Initialize Libaries
SoftwareSerial modbusSerial(SoftRO, SoftDI); // RX TX
ModbusRTUSlave modbus(modbusSerial, DERE); // Create Modbus Object

bool coils[1] = {1};
uint16_t InputRegisters[1];


void setup() {
  modbus.configureCoils(coils, 1);
  modbus.configureInputRegisters(InputRegisters, 1);
  modbus.begin(ID, 9600);          // ID | Baud Rate
  Serial.begin(9600);              // For Debuging
}

void loop() {
modbus.poll();
// Serial.println(Serial.available());
// Serial.println(modbusSerial.available());
    if (coils[0] == 1) {
        coils[0] = 0;
        InputRegisters[0] = random(0, 65536);
        Serial.print("Changed to: "); // Debugging Line
        Serial.println(InputRegisters[0]);
    }
delay(500);
}