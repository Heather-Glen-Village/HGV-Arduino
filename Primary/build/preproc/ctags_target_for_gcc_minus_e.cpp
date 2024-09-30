# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
//#define DI 0
//#define RO 1


const int DERE_POWER = 1;

void setup() {
    pinMode(2, 0x1);
    pinMode(8, 0x1);
    Serial.begin(9600);
    digitalWrite(8, DERE_POWER);
    digitalWrite(2, DERE_POWER);
}

void loop(){

    if(Serial.available() > 0){
        String IncomingMessage = Serial.readString();
        Serial.print("Received: ");
        Serial.println(IncomingMessage);
        if(IncomingMessage == "Test") {
            digitalWrite(2, !digitalRead(2));
        }
    }
}
