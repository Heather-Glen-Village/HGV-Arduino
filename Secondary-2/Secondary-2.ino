#include <SoftwareSerial.h>

#define SoftDI 16 // A2
#define SoftRO 17 // A3
#define LED 2
#define DERE 9
#define DERE_POWER HIGH

SoftwareSerial RS485Serial(SoftRO, SoftDI); // RX TX


void setup() {
    pinMode(LED, OUTPUT);
    pinMode(DERE, OUTPUT);
    Serial.begin(9600);
    RS485Serial.begin(9600);
    
    digitalWrite(DERE, DERE_POWER);
    digitalWrite(LED, HIGH);
}

void loop(){
  Serial.print("a"); // send a message 
  delay(1000);
  RS485Serial.print("a"); // send a message
  delay(5000);

}
