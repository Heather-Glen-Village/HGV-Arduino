#if (defined __AVR_ATmega328P__ || defined __AVR_ATmega168__ || defined __AVR_ATmega1280__ || defined __AVR_ATmega2560__)
  #include <SoftwareSerial.h>
#endif

#include <ModbusRTUSlave.h>

const byte dePin = 9;

#if (defined __AVR_ATmega328P__ || defined __AVR_ATmega168__ || defined __AVR_ATmega1280__ || defined __AVR_ATmega2560__)
  const byte rxPin = 10;
  const byte txPin = 11;
  SoftwareSerial mySerial(rxPin, txPin);
  ModbusRTUSlave modbus(mySerial, dePin);
#elif defined ESP32
  ModbusRTUSlave modbus(Serial0, dePin);
#else
  ModbusRTUSlave modbus(Serial1, dePin);
#endif

uint16_t holdingRegisters[2];
float *floatRegisters = (float*)holdingRegisters;

void setup() {
  modbus.configureHoldingRegisters(holdingRegisters, 2); // unsigned 16 bit integer array of holding register values, number of holding registers
  modbus.begin(1, 38400);
  Serial.begin(115200);
  while(!Serial);
}

void loop() {
  float oldFloatValue = floatRegisters[0];
  modbus.poll();
  if (floatRegisters[0] != oldFloatValue) {
    Serial.println(floatRegisters[0], 5);
  }
}