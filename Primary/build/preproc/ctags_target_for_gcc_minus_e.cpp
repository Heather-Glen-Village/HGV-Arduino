# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
const int buzzer = 7;
const int led = 2;

void setup(){
  pinMode(buzzer, 0x1);
  pinMode(led, 0x1);
}

void loop(){
  digitalWrite(led, 0x1);
  // digitalWrite(buzzer, LOW);
  // delay(500);
  // digitalWrite(led, LOW);
  // digitalWrite(buzzer, LOW);
  // delay(2500);
}
