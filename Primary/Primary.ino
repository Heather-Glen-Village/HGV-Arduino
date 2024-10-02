#include <ArduinoRS485.h>
#include <RS485.h>


//#define DI 0
//#define RO 1
#define LED 2
#define DERE 8

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(DERE, OUTPUT);
    Serial.begin(9600);
}

void loop(){

}