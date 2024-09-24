# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"





void setup() {
    pinMode(2, 0x1);
    pinMode(8, 0x1);
    Serial.begin(9600);
    digitalWrite(8, 0x0);
}

void loop(){
    digitalWrite(8, 0x1);
    delay(10);
    Serial.write("A");
    Serial.flush();
    digitalWrite(8, 0x0);
    delay(1000);


}
