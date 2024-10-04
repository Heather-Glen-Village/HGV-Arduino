#include <ModbusRTUSlave.h>

// Pins List

//#define TX  0
//#define RX  1
#define DERE  9
#define LED   2

ModbusRTUSlave modbus(Serial, DERE); // Create Modbus Object

bool coils[1]; // Creating an array where the Coils can go | Read & Write Only Bools

void setup() {
  pinMode(LED, OUTPUT);

  modbus.configureCoils(coils, 1); // Says where The Coils can go and How many there are?
  modbus.begin(1, 9600); // ID | Baud Rate  | Config?
  Serial.begin(9600);
  
}

void loop() {
  if (Serial.available() != 0){
    Serial.println("LED Change");
    modbus.poll(); // Check if there was a request

    digitalWrite(LED, coils[0]);
  }

  delay(500);
}