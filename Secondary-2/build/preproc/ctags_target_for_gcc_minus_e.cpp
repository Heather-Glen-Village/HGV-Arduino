# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"



void setup(){
  pinMode(2, 0x1);
  Serial.begin(9600);
}

void loop(){
    while(Serial.available()) // if there is something to read in the serial
    {
        digitalWrite(2, 0x0);
        if(Serial.read() == 'A')
        {
            //digitalWrite(LED, !digitalRead(LED));
            Serial.println("Message received");

        }
    }
    digitalWrite(2, 0x1);
}
