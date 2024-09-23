# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"





void setup(){
    digitalWrite(2, 0x1);
    digitalWrite(8, 0x1);
    Serial.begin(9600);
    digitalWrite(8, 0x0);
}

void loop(){
    while(Serial.available())
    {
        char Message = Serial.read();
        Serial.println(Message);
        if(Message == 'A')
        {
            digitalWrite(2, !digitalRead(2));
        }
    }
}
