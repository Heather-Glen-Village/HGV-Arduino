#include <Arduino.h>
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
#include <ModbusRTUMaster.h>

// Pins List

//#define TX  0
//#define RX  1
#define DERE  9
#define LED   2

ModbusRTUSlave modbus(Serial, DERE); // Create Modbus Object

bool coils[1]; // Creating an array where the Coils can go | Read & Write Only Bools

#line 14 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void setup();
#line 21 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void loop();
#line 14 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void setup() {
  pinMode(LED, OUTPUT);

  modbus.configureCoils(coils, 1); // Says where The Coils can go and How many there are?
  modbus.begin(1, 9600); // ID | Baud Rate  | Config?
}

void loop() {
    //modbus.setResponseDelay(responseDelay) | used to make delay from the resonds

  modbus.poll(); // Check if there was a request

  digitalWrite(LED, coils[0]);
  delay(100);
}
