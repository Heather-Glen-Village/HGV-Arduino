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

void loop() {
  int Serial_A = Serial.available();
  int Soft_A = RS485Serial.available();
  Serial.print(Serial_A);
  Serial.print(Soft_A);
  if (Serial_A > 0)
  {
    String IncomingMessage = Serial.readString();
    Serial.print("Received: ");
    Serial.println(IncomingMessage);
    Serial.println(IncomingMessage == "a");
    if (IncomingMessage == "a")
    {
      bool led_power = !digitalRead(LED);
      Serial.println(led_power);
      digitalWrite(LED, led_power);
    }
  }
  else if (Soft_A > 0)
  {
    String IncomingMessage = RS485Serial.readString();
    Serial.print("Received: ");
    Serial.println(IncomingMessage);
    if (IncomingMessage == "Test")
    {
      bool led_power = !digitalRead(LED);
      Serial.println(led_power);
      digitalWrite(LED, !digitalRead(LED));
    }
  }
  delay(500);
}
