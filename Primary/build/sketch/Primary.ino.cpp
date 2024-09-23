#include <Arduino.h>
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
const int buzzer = 7;
const int led = 2;
  
#line 4 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void setup();
#line 9 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void loop();
#line 4 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void setup(){
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
}
  
void loop(){
  digitalWrite(led, HIGH);
  // digitalWrite(buzzer, LOW);
  // delay(500);
  // digitalWrite(led, LOW);
  // digitalWrite(buzzer, LOW);
  // delay(2500);
}
