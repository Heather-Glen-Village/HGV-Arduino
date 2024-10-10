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

void setup()
{
  pinMode(LED, OUTPUT);

  modbus.begin(9600);
  Serial.begin(9600); // For Debuging
}

void loop()
{
  digitalWrite(LED, SlaveLED); // Matches Slave LED With Board LED

  uint8_t returncode = modbus.writeSingleCoil(1, 0, SlaveLED); // Write to Coil of Board id=1
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