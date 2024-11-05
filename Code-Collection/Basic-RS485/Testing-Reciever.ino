#include <SoftwareSerial.h>

#define SoftDI 16 // A2
#define SoftRO 17 // A3
//#define DI 0
//#define RO 1
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

  if (Serial_A > 0) {
    Serial.println(Serial_A);
    char IncomingMessage = Serial.read();

    Serial.print("Received: ");
    Serial.println(IncomingMessage);
    
    bool led_power = !digitalRead(LED);
    Serial.println(led_power);
    digitalWrite(LED, led_power);

  }
  else if (Soft_A > 0) {
    Serial.println(Soft_A);
    String IncomingMessage = RS485Serial.readString();
    Serial.print("Received: ");
    Serial.println(IncomingMessage);
    
    bool led_power = !digitalRead(LED);
    digitalWrite(LED, led_power);
  }
  delay(500);
}