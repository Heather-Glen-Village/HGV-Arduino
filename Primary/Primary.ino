//#define DI 0
//#define RO 1

#include<SoftwareSerial.h>

#define SoftDI 14 // A0
#define SoftRO 15 // A1
#define LED 2
#define DERE 9
#define DERE_POWER LOW

SoftwareSerial RS485Serial(SoftRO, SoftDI); // RX TX


void setup() {
    pinMode(LED, OUTPUT);
    pinMode(DERE, OUTPUT);
    Serial.begin(9600);
    digitalWrite(DERE, DERE_POWER);
}

void loop(){
    Serial.print("Serial Available: ");
    Serial.println(Serial.available());
    Serial.print("Software Serial Available: ");
    Serial.println(RS485Serial.available());
    delay(1000);
    
}