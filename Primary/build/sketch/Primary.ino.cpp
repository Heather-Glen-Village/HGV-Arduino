#include <Arduino.h>
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
#define DI 0
#define RO 1
#define LED 2
#define MASTER_EN 8

#line 6 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void setup();
#line 13 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void loop();
#line 6 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void setup() {
    pinMode(LED, OUTPUT);
    pinMode(MASTER_EN, OUTPUT);
    Serial.begin(9600);
    digitalWrite(MASTER_EN, LOW);
}

void loop(){
    digitalWrite(MASTER_EN, HIGH);
    delay(10);
    Serial.write("A");
    Serial.flush();
    digitalWrite(MASTER_EN, LOW);
    delay(1000);
    

}
