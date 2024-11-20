#include <SoftwareSerial.h>

#define SoftDI 17 // A2
#define SoftRO 16 // A3
// #define DI 0
// #define RO 1
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
    digitalWrite(DERE, DERE_POWER);

    int Serial_A = Serial.available();
    int Soft_A = RS485Serial.available();

    if (Serial_A > 0)
    {
        Serial.println(Serial_A);
        String IncomingMessage = Serial.readString();

        Serial.print("Received Hardware: ");
        Serial.println(IncomingMessage);
    }
    else if (Soft_A > 0)
    {
        Serial.println(Soft_A);
        String IncomingMessage = RS485Serial.readString();
        Serial.print("Received: ");
        Serial.println(IncomingMessage);
        RS485Serial.flush();
    }
}