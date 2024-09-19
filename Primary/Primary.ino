const int buzzer = 7;
const int led = 2;
  
void setup(){
	pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
}
  
void loop(){
  digitalWrite(led, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  digitalWrite(buzzer, LOW);
  delay(2500);
}