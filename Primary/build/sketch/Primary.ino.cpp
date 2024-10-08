#include <Arduino.h>
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
#include <SoftwareSerial.h>
#include <ModbusRTUMaster.h>

// Pins List
#define SoftTX 14 // Phyical TX 0
#define SoftRX 15 // Phyical RX 1
#define DERE 9
#define LED 2

// Initialize Library
//SoftwareSerial modbusSerial(SoftRX, SoftTX);
ModbusRTUMaster modbus(Serial, DERE); // Create Modbus Object with port for RS485

bool SlaveLED = 1; // Enable Slave LED by default

#line 16 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void setup();
#line 24 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void loop();
#line 16 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void setup()
{
  pinMode(LED, OUTPUT);

  modbus.begin(9600);
  Serial.begin(9600); // For Debuging
}

void loop()
{
  digitalWrite(LED, SlaveLED); // Matches Slave LED With Board LED

  modbus.writeSingleCoil(0, 0, SlaveLED); // 0 sends to all boards
  if (SlaveLED == 1)
  { // Turns LED off if on and vice versa
    SlaveLED = 0;
    Serial.println("SlaveLED Enabled");
  }
  else
  {
    SlaveLED = 1;
    Serial.println("SlaveLED Disabled");
  }
  delay(2000);
}
