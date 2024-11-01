// #define DI 0
// #define RO 1

#include <SoftwareSerial.h>

#define SoftDI 14 // A0
#define SoftRO 15 // A1
#define LED 2
#define DERE 9
#define DERE_POWER LOW

SoftwareSerial RS485Serial(SoftRO, SoftDI); // RX TX

void setup()
{
    pinMode(LED, OUTPUT);
    pinMode(DERE, OUTPUT);
    Serial.begin(9600);
    RS485Serial.begin(9600);
    digitalWrite(DERE, DERE_POWER);
}

void loop()
{
    Serial.print("Serial Available: ");
    Serial.println(Serial.available());
    Serial.print("Software Serial Available: ");
    Serial.println(RS485Serial.available());
    delay(1000);
}

void loop()
{
    if (Serial.available() > 0)
    {
        String IncomingMessage = Serial.readString();
        Serial.print("Received: ");
        Serial.println(IncomingMessage);
        if (IncomingMessage == "Test")
        {
            digitalWrite(LED, !digitalRead(LED));
        }
    }
    else if (RS485Serial.available() > 0)
    {
        String IncomingMessage = Serial.readString();
        Serial.print("Received: ");
        Serial.println(IncomingMessage);
        if (IncomingMessage == "Test")
        {
            digitalWrite(LED, !digitalRead(LED));
        }
    }
}
