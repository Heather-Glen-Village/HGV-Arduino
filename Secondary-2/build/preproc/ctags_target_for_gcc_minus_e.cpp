# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
void setup()
{
    Serial.begin(9600);
    pinMode(2, 0x1);
}

void loop()
{
 digitalWrite(14, 0x1);
    Serial.println("High");
    delay(1000);
    digitalWrite(14, 0x0);
    Serial.println("Low");
    delay(1000);
}
