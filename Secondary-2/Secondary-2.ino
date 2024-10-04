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
  modbus.setResponseDelay(2000) //| used to make delay from the resonds
  modbus.begin(2, 9600); // ID | Baud Rate  | Config?
}

void loop() {

  modbus.poll(); // Check if there was a request

  digitalWrite(LED, coils[0]);
  
}