#include <SoftwareSerial.h>

#define SoftDI 16 // A2
#define SoftRO 17 // A3
//#define DI 0
//#define RO 1
#define LED 2
#define DERE 9


SoftwareSerial RS485Serial(SoftRO, SoftDI); // RX TX

#define DERE_POWER HIGH
void setup() {
    pinMode(LED, OUTPUT);
    pinMode(DERE, OUTPUT);
    Serial.begin(9600);
    
    digitalWrite(DERE, DERE_POWER);
    digitalWrite(LED, HIGH);
}

void loop(){
  Serial.print("Test"); // send a message 
  Serial.flush(); // wait till Primary get the message
  delay(1000);
  RS485Serial.print("Test"); // send a message
  RS485Serial.flush(); // wait till Primary get the message
  delay(5000);

}