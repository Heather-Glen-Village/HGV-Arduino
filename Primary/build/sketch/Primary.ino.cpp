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
SoftwareSerial modbusSerial(SoftRX, SoftTX);
ModbusRTUMaster modbus(Serial, DERE); // Create Modbus Object with port for RS485

bool SlaveLED = 1; // Enable Slave LED by default

uint16_t randomfloat_UINT16[];
float *randomfloat = (float*)randomfloat_UINT16;

uint16_t randomtime_UINT16[];
float *randomtime = (float*)randomtime_UINT16;

#line 22 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void setup();
#line 30 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void loop();
#line 22 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void setup()
{
  pinMode(LED, OUTPUT);

  modbus.begin(9600);
  Serial.begin(9600); // For Debuging
}

void loop()
{
  if (modbus)

  if (returncode == 0)
  {
    if (SlaveLED == 1)
    {
      SlaveLED = 0;
      Serial.println("SlaveLED Enabled");
    }
    else
    {
      SlaveLED = 1;
      Serial.println("SlaveLED Disabled");
    }
  }
  else
  {
    // Shows error Message in Debug Terminal
    Serial.print("S1 Code: ");
    Serial.println(returncode);
  }
  delay(2000);
}
