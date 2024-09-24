#define led 2
  
void setup(){
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}
  
void loop(){
  digitalWrite(led, HIGH);
  Serial.println(digitalRead(led));
  // delay(500);
  // digitalWrite(led, LOW);
  // delay(2500);
}