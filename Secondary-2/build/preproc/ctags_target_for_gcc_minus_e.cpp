# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"



void setup(){
  pinMode(2, 0x1);
  pinMode(1 /* Change this to RS485 Pin*/, 0x1);
  Serial.begin(9600);
  digitalWrite(1 /* Change this to RS485 Pin*/, 0x0);
}

void loop(){
    while(Serial.available()) // if there is something to read in the serial
    {
        Serial.println(Serial.read());
        if(Serial.read() == 'A')
        {
            digitalWrite(2, !digitalRead(2));
        }
    }
}
