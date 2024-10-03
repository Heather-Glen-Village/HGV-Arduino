
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

#define TX 0
// RX 1
#define DE 9
#define RE 9

#define LED 2

void setup()
{
    RS485.setPins(TX, DE, RE);
    RS485.begin(9600);
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
	
}

void loop()
{
    Serial.println(RS485.available());
    if(RS485.available() > 0){
        String IncomingMessage = RS485.readString();
        Serial.print("Received: ");
        Serial.println(IncomingMessage);
        if(IncomingMessage == "Test") {
            digitalWrite(LED, !digitalRead(LED));
        }
    }
}
