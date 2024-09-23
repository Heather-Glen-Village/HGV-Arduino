#define LED 2
#define MASTER_EN 0 // Change this to RS485 Pin

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(MASTER_EN, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  digitalWrite(MASTER_EN, LOW);
  pinMode(8, LOW);
}
  
void loop(){
  digitalWrite(MASTER_EN, HIGH); // Enable Pin to Send Data
  digitalWrite(8, HIGH);
  delay(5);
  Serial.println('test');
  Serial.flush(); // Wait for data to send
  digitalWrite(MASTER_EN, LOW);
  pinMode(8, LOW);
  delay(1000);

}