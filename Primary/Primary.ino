#include <SoftwareSerial.h>
//#include <NeoSWSerial.h>
#include <ModbusRTUMaster.h>

// Pins List

#define TX    14 //Phyical TX 0
#define RX    15 //Phyical RX 1
#define DERE  9
#define LED   2
SoftwareSerial modbusSerial(RX, TX);
ModbusRTUMaster modbus(modbusSerial, DERE); // Create Modbus Object with port for RS485


bool SlaveLED = 1; // Enable

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, SlaveLED);
  //modbus.setTimeout(500);
  modbus.begin(9600); // Baud Rate  | Config?
  Serial.begin(9600);
}

void loop() {
  digitalWrite(LED, SlaveLED);
  uint8_t returncode = modbus.writeSingleCoil(2, 0, SlaveLED);
  // delay(5000);
  // uint8_t returncode2 = modbus.writeSingleCoil(2, 0, SlaveLED);
  if (returncode == 0) {
    if (SlaveLED == 1) {
      SlaveLED = 0;
      Serial.println("SlaveLED Enabled");
    } 
    else {
      SlaveLED = 1;
      Serial.println("SlaveLED Disabled");
    }
  }
  else{
    Serial.print("Error Code: ");
    Serial.println(returncode);
    // Serial.print("S2 Code: ");
    // Serial.println(returncode2);
  }

  delay(5000);
}