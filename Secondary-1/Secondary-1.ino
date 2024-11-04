#include <SoftwareSerial.h>

#define SoftDI 16 // A2
#define SoftRO 17 // A3
#define LED 2
#define DERE 9
#define DERE_POWER HIGH

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
  Serial.print(Serial.available());
  Serial.print(RS485Serial.available());
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
    String IncomingMessage = RS485Serial.readString();
    Serial.print("Received: ");
    Serial.println(IncomingMessage);
    if (IncomingMessage == "Test")
    {
      digitalWrite(LED, !digitalRead(LED));
    }
  }
  delay(500);
}
