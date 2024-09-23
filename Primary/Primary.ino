#define LED 2
#define MASTER_EN 0 // Change this to RS485 Pin

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(MASTER_EN, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  digitalWrite(MASTER_EN, LOW);
  pinMode(8, HIGH);
}
  
void loop(){
  digitalWrite(MASTER_EN, HIGH); // Enable Pin to Send Data
  delay(5);
  Serial.println('A');
  Serial.flush(); // Wait for data to send
  digitalWrite(MASTER_EN, LOW);
  delay(1000);

}