#include <SoftwareSerial.h>
#include <ModbusRTUMaster.h>

// Pins List

#define TX    14 //Phyical TX 0
#define RX    15 //Phyical RX 1
#define DERE  9
#define LED   2

SoftwareSerial modbusSerial(RX, TX); // Create a Serial Terminal for the Rs485 to Use
ModbusRTUMaster modbus(modbusSerial, DERE); // Create Modbus Object with port for RS485


bool SlaveLED = 1; // Default to Enable LED

void setup() {
  pinMode(LED, OUTPUT);
  modbus.begin(9600);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(LED, SlaveLED);
  modbus.writeSingleCoil(0,0,SlaveLED);
  if (SlaveLED == 1) {
      SlaveLED = 0;
      Serial.println("SlaveLED Enabled");
    } 
    else {
      SlaveLED = 1;
      Serial.println("SlaveLED Disabled");
    }


  /*uint8_t returncode = modbus.writeSingleCoil(1, 0, SlaveLED);
  delay(1000);
  uint8_t returncode2 = modbus.writeSingleCoil(2, 0, SlaveLED);
  if (returncode == 0 && returncode2 == 0) {
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
    Serial.print("S1 Code: ");
    Serial.println(returncode);
    Serial.print("S2 Code: ");
    Serial.println(returncode2);
  }*/

  delay(5000);
}