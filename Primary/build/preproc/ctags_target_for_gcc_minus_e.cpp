# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
//#define DI 0
//#define RO 1



void setup() {
    pinMode(2, 0x1);
    pinMode(9, 0x1);
    Serial.begin(9600);
}

void loop(){
    digitalWrite(2, 0x0);
    Serial.println("Primary Board Code");
    delay(1000);
}
