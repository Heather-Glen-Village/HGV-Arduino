#include <Arduino.h>
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"

// Rs485 Library
#include <ArduinoRS485.h>
#include <RS485.h>
//Modbus Library
#include <ArduinoModbus.h>
#include <ModbusClient.h>
#include <ModbusRTUClient.h>
#include <ModbusRTUServer.h>
#include <ModbusServer.h>
#include <ModbusTCPClient.h>
#include <ModbusTCPServer.h>

// Pins

#define TX    0
//      RX    1
#define DE    9
#define RE    9

#define LED   2

#line 23 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void setup();
#line 31 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void loop();
#line 23 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void setup()
{
    RS485.setPins(TX, DE, RE);
    RS485.begin(9600);
    pinMode(LED, OUTPUT);
	
}

void loop()
{
	RS485.beginTransmission();
    RS485.println("Test");
    RS485.endTransmission();
    delay(1000);
}

