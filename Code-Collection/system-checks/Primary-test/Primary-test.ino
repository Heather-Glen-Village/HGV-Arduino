#include <ModbusRTUMaster.h>

// Settings you need to Change
#define NumSecondary 1 // Amount of Secondary Boards Being Used
// Don't Touch
#define RS485Serial Serial // Which Serial Is being Used
#define baud 9600

ModbusRTUMaster modbus(RS485Serial);
uint16_t DiscreteInputs[1];
uint16_t RandomNum;

bool errorCheck(uint8_t errorCode)
{
    if (errorCode == 0)
    {
        return true;
    }
    else
    {
        Serial.print("Modbus error: " + String(errorCode) + "-");
        if (errorCode == 1)
        {
            Serial.println("Invalid Unit ID");
        }
        else if (errorCode == 2)
        {
            Serial.println("Invalid buffer");
        }
        else if (errorCode == 3)
        {
            Serial.println("Invalid quantity");
        }
        else if (errorCode == 4)
        {
            Serial.println("Response timeout");
        }
        else if (errorCode == 5)
        {
            Serial.println("Frame error");
        }
        else if (errorCode == 6)
        {
            Serial.println("CRC error");
        }
        else if (errorCode == 7)
        {
            Serial.println("Unknown communication error");
        }
        else if (errorCode == 8)
        {
            Serial.println("Unexpected unit ID in response");
        }
        else if (errorCode == 9)
        {
            Serial.println("Exception response");
        }
        else if (errorCode == 10)
        {
            Serial.println("Unexpected function code in response");
        }
        else if (errorCode == 11)
        {
            Serial.println("Unexpected response length");
        }
        else if (errorCode == 12)
        {
            Serial.println("Unexpected byte count in response");
        }
        else if (errorCode == 13)
        {
            Serial.println("Unexpected data address in response");
        }
        else if (errorCode == 14)
        {
            Serial.println("Unexpected data value in response");
        }
        else if (errorCode == 15)
        {
            Serial.println("Unexpected quantity in response");
        }
        return false;
    }
}

// ----------Basic Setup and Loop Start Here ----------
void setup()
{
    // Starts all Serial and Modbus Communication
    Serial.begin(baud);
    modbus.begin(baud);
    Serial.println("Primary Board Modbus Test");
    delay(1000);
}

void loop()
{
    Serial.println("=====================================================================");
    Serial.println("Step 1: Reading Message from Secondary's");
    for (int i = 1; i < NumSecondary + 1; i++)
    {
        Serial.println("======================================");
        Serial.print("Reading from Secondary ");
        Serial.println(i);
        delay(1000);
        int IR = errorCheck(modbus.readInputRegisters(i, 0, DiscreteInputs, 1));
        if (IR == i)
        {
            Serial.print("Was Able to Read a Message from Secondary ");
            Serial.println(i);
        }
        else
        {
            Serial.print("Failed to Read a Message from Secondary ");
            Serial.println(i);
        }
        delay(1000);
    }
    Serial.println("=====================================================================");
    Serial.println("Step 2: Writing Random Number to Secondary's");
    for (int i = 1; i < NumSecondary + 1; i++)
    {
        Serial.println("======================================");
        RandomNum = random(0, 1000);
        Serial.print("Sending Random Number: ");
        Serial.print(RandomNum);
        Serial.print(" to Secondary ");
        Serial.println(i);
        delay(1000);
        if (errorCheck(modbus.writeSingleHoldingRegister(i, 0, RandomNum)))
        {
            Serial.print("Was Able to Write Random Number to Secondary ");
            Serial.println(i);
        }
        else
        {
            Serial.println("May have Failed to Write to Secondary, Check Secondary Terminal to Confirm");
        }
        delay(1000);
    }
    Serial.println("Done Testing, Will Repeat Soon");
    delay(5000);
}
