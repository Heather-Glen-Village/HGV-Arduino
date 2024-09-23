#include <Arduino.h>
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
void setup();
#line 7 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
void loop();
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
void setup()
{
    Serial.begin(9600);
    pinMode(2, OUTPUT);
}

void loop()
{
	digitalWrite(2, HIGH);
    Serial.println("High");
    delay(1000);
    digitalWrite(2, LOW);
    Serial.println("Low");
    delay(1000);
}

