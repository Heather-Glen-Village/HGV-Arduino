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
#define ID 2

// Initialize Libaries
SoftwareSerial modbusSerial(SoftRX, SoftTX);
ModbusRTUSlave modbus(modbusSerial, DERE); // Create Modbus Object

bool coils[1] = {1};
uint16_t InputRegisters[1];


void setup() {
  pinMode(LED, OUTPUT);

  modbus.configureCoils(coils, 1);
  modbus.configureInputRegisters(InputRegisters, 1);
  modbus.begin(ID, 9600);          // ID | Baud Rate
  Serial.begin(9600);              // For Debuging
}

void loop() {
modbus.poll();
    if (coils[0] == 1) {
        coils[0] = 0;
        InputRegisters[0] = random(0, 65536);
        Serial.print("Changed to: "); // Debugging Line
        Serial.println(InputRegisters[0]);
    }
delay(500);
}