# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
//#define DI 0
//#define RO 1




void setup() {
    pinMode(2, 0x1);
    pinMode(9, 0x1);
    Serial.begin(9600);

    digitalWrite(9, 0x1);
    digitalWrite(2, 0x1);
}

void loop(){
  Serial.print("Test"); // send a message 
  Serial.flush(); // wait till Primary get the message
  delay(5000);
}
