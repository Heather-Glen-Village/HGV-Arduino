#include <Arduino.h>
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
#include <ModbusRTUSlave.h>

// Pins List

//#define TX  0
//#define RX  1
#define DERE  9
#define LED   2

ModbusRTUSlave modbus(Serial, DERE); // Create Modbus Object

bool coils[1]; // Creating an array where the Coils can go | Read & Write Only Bools

#line 14 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void setup();
#line 24 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void loop();
#line 14 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void setup() {
  pinMode(LED, OUTPUT);

  modbus.configureCoils(coils, 1); // Says where The Coils can go and How many there are?
  //odbus.setResponseDelay(1500); //| used to make delay from the resonds
  modbus.begin(1, 9600); // ID | Baud Rate  | Config?
   

}

void loop() {
   
  modbus.poll(); // Check if there was a request

  digitalWrite(LED, coils[0]);
 // delay(100);
}
