#include <ModbusRTUMaster.h>
//#include <SoftwareSerial.h>

// Pins List
//#define SoftTX 14 // Phyical TX 0
//#define SoftRX 15 // Phyical RX 1
#define DERE 9
#define LED 2

// Initialize Library
ModbusRTUMaster modbus(Serial, DERE); // Create Modbus Object with port for RS485

//Buffer and Pointers

uint16_t buffer[2];
float *Floatbuffer = (float*)buffer; // Used for Temperature and Humidity


// Storage Array
uint16_t time[1];
float temperature[2];
float humidity[2];
bool motion[1];
uint16_t vibration[1];
uint16_t water[1];
uint16_t smoke[1];





void setup() {
  pinMode(LED, OUTPUT);

  modbus.begin(19200);
  Serial.begin(9600); // For Debuging
}

void loop() {
  Serial.println("Float: "+ String(readFloat(1)));
  delay(1000);
}

float readFloat(uint16_t ID) {
  modbus.writeSingleCoil(1,0,1); // Tell it to Sense
  delay(3000); // Need to Edit Time
  uint16_t returncode = modbus.readInputRegisters(ID, 0, buffer, 2);
  Serial.println(returncode);
  debug(returncode);
  return Floatbuffer[0];
}


const char* errorStrings[] = {
  "success",
  "invalid id",
  "invalid buffer",
  "invalid quantity",
  "response timeout",
  "frame error",
  "crc error",
  "unknown comm error",
  "unexpected id",
  "exception response",
  "unexpected function code",
  "unexpected response length",
  "unexpected byte count",
  "unexpected address",
  "unexpected value",
  "unexpected quantity"
};
bool debug(uint16_t returncode) {
  if (returncode == 0) {
    Serial.println();
    Serial.println(String(returncode) + ", " + errorStrings[returncode]);
    return true;
  }
  else {
    Serial.println();
    Serial.println("Error: " + String(returncode) + ", " + errorStrings[returncode]);
    return false;
  }
}

