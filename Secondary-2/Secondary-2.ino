#include <SoftwareSerial.h>

#define SoftDI 16 // A2
#define SoftRO 17 // A3
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
    
    bool led_power = !digitalRead(LED);
    Serial.println(led_power);
    digitalWrite(LED, led_power);

  }
  if (Soft_A > 0)
  {
    Serial.println("We Got Something on Soft Serial");
    Serial.println(RS485Serial.readString());
    String IncomingMessage = RS485Serial.readString();
    Serial.print("Received: ");
    Serial.println(IncomingMessage);
    
    bool led_power = !digitalRead(LED);
    Serial.println(led_power);
    digitalWrite(LED, led_power);
  }
  delay(500);
}
