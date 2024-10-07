#include <Arduino.h>
#line 1 "D:\\Github\\HGV\\rems006-Arduino\\Primary\\Primary.ino"
#include <SoftwareSerial.h>
#include <ModbusRTUMaster.h>
#include <ModbusRTUSlave.h>

// Pins List
#define SoftTX 14 // Phyical TX 0
#define SoftRX 15 // Phyical RX 1
#define DERE 9
#define LED 2

// Initialize Library
SoftwareSerial modbusSerial(SoftRX, SoftTX);
ModbusRTUMaster modbus(modbusSerial, DERE); // Create Modbus Object with port for RS485

bool SlaveLED = 1; // Enable Slave LED by default

#line 17 "D:\\Github\\HGV\\rems006-Arduino\\Primary\\Primary.ino"
void setup();
#line 25 "D:\\Github\\HGV\\rems006-Arduino\\Primary\\Primary.ino"
void loop();
#line 17 "D:\\Github\\HGV\\rems006-Arduino\\Primary\\Primary.ino"
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
  delay(5000);
}
