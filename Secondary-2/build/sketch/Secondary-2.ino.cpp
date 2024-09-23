#include <Arduino.h>
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
#define LED 2
#define SLAVE_EN 1 // Change this to RS485 Pin
  
#line 4 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
void setup();
#line 11 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
void loop();
#line 4 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
void setup(){
  pinMode(LED, OUTPUT);
  pinMode(SLAVE_EN, OUTPUT);
  Serial.begin(9600);
  digitalWrite(SLAVE_EN, LOW);
}
  
void loop(){
    while(Serial.available()) // if there is something to read in the serial
    {
        Serial.println(Serial.read());
        if(Serial.read() == 'A')
        {
            digitalWrite(LED, !digitalRead(LED));
        }
    }
}
