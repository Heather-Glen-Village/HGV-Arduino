#include <Arduino.h>
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
//#define DI 0
//#define RO 1
#define LED 2
#define DERE 9

#define DERE_POWER HIGH
#line 7 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void setup();
#line 16 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void loop();
#line 7 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
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
  delay(5000);
}
