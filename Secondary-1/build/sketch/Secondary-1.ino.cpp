#include <Arduino.h>
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
#include <SoftwareSerial.h>

#define SoftDI 16 // A2
#define SoftRO 17 // A3
//#define DI 0
//#define RO 1
#define LED 2
#define DERE 8
#define DERE_POWER LOW

SoftwareSerial RS485Serial(SoftRO, SoftDI); // RX TX

#line 13 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void setup();
#line 22 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void loop();
#line 13 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(DERE, OUTPUT);
  Serial.begin(9600);
  RS485Serial.begin(19200);
  digitalWrite(DERE, DERE_POWER);
}

void loop() {
  digitalWrite(DERE, DERE_POWER);

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
    bool IncomingMessage = RS485Serial.read();
    Serial.print("Received: ");
    Serial.println(IncomingMessage);
    if (IncomingMessage == 1) {
      digitalWrite(LED, !digitalRead(LED));
    }
    else {
      Serial.println("Unknown message");
    }
  }

}
