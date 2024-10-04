#include <Arduino.h>
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
#include <ModbusRTUMaster.h>

// Pins List

//#define TX  0
//#define RX  1
#define DERE  9
#define LED   2

ModbusRTUMaster modbus(Serial, DERE); // Create Modbus Object with port for RS485

bool SlaveLED = 1; // Enable

#line 14 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void setup();
#line 22 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void loop();
#line 14 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  //modbus.setTimeout(500);
  modbus.begin(9600); // Baud Rate  | Config?
  Serial.begin(9600);
}

void loop() {
  if (modbus.writeSingleCoil(1, 0, SlaveLED) == 0) {
    SlaveLED = !SlaveLED;
  }
  else{
    Serial.println(modbus.getExceptionResponse());
  }
  
  delay(2000);
}
