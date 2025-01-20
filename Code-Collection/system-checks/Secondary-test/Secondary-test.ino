#include <ModbusRTUSlave.h>
#include <SoftwareSerial.h>

// Settings you need to Change
#define Secondary 1 // Which Secondary This is
// Don't Touch
#define RS485Serial SoftSerial // Which Serial Is being Used
#define baud 9600

SoftwareSerial SoftSerial(8, 9); // D8 Tx D9 Rx
ModbusRTUSlave modbus(RS485Serial);
uint16_t HoldingRegisters[1];
uint16_t InputRegisters[1] = {Secondary};
uint16_t OldHolding = 0;

void setup()
{
    modbus.configureHoldingRegisters(HoldingRegisters, 1);
    modbus.configureInputRegisters(InputRegisters, 1);
    Serial.begin(baud);
    modbus.begin(Secondary, baud);

    Serial.println("Secondary Board Modbus Test");
    Serial.print("Secondary Board: ");
    Serial.println(Secondary);
    Serial.println("Will Only Print Messages on Step 2 if Getting a Message");
    delay(1000);
}

void loop()
{
    if (Serial.available())
    {
        modbus.poll();
        if (OldHolding != HoldingRegisters[0])
        {
            Serial.print("Holding Register Changed: ");
            Serial.println(HoldingRegisters[0]);
            OldHolding = HoldingRegisters[0];
        }
    }
}