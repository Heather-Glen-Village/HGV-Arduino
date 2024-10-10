#if (defined __AVR_ATmega328P__ || defined __AVR_ATmega168__ || defined __AVR_ATmega1280__ || defined __AVR_ATmega2560__)
  #include <SoftwareSerial.h>
#endif

#include <ModbusRTUMaster.h>

const byte dePin = 9;

#if (defined __AVR_ATmega328P__ || defined __AVR_ATmega168__ || defined __AVR_ATmega1280__ || defined __AVR_ATmega2560__)
  const byte rxPin = 10;
  const byte txPin = 11;
  SoftwareSerial mySerial(rxPin, txPin);
  ModbusRTUMaster modbus(mySerial, dePin);
#elif defined ESP32
  ModbusRTUMaster modbus(Serial0, dePin);
#else
  ModbusRTUMaster modbus(Serial1, dePin);
#endif

uint16_t holdingRegisters[2];
float *floatRegisters = (float*)holdingRegisters;

void setup() {
  modbus.begin(38400);
  Serial.begin(115200);
  Serial.setTimeout(10);
  while(!Serial);
}

void loop() {
  if (Serial.available()) {
    String string = Serial.readStringUntil('\n');
    string.trim();
    floatRegisters[0] = string.toFloat();
    Serial.print("Sending: ");
    Serial.println(floatRegisters[0], 5);
    debug(modbus.writeMultipleHoldingRegisters(1, 0, holdingRegisters, 2));
  }
}


bool debug(bool modbusRequest) {
  if (modbusRequest == true) {
    Serial.println("Success");
  }
  else {
    Serial.print("Failure");
    if (modbus.getTimeoutFlag() == true) {
      Serial.print(": Timeout");
      modbus.clearTimeoutFlag();
    }
    else if (modbus.getExceptionResponse() != 0) {
      Serial.print(": Exception Response ");
      Serial.print(modbus.getExceptionResponse());
      switch (modbus.getExceptionResponse()) {
        case 1:
          Serial.print(" (Illegal Function)");
          break;
        case 2:
          Serial.print(" (Illegal Data Address)");
          break;
        case 3:
          Serial.print(" (Illegal Data Value)");
          break;
        case 4:
          Serial.print(" (Server Device Failure)");
          break;
        default:
          Serial.print(" (Uncommon Exception Response)");
          break;
      }
      modbus.clearExceptionResponse();
    }
    Serial.println();
  }
  Serial.flush();
  return modbusRequest;
}