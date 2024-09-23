#define LED 2
#define MASTER_EN 0 // Change this to RS485 Pin

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  pinMode(8, HIGH);
}
  
void loop(){
  delay(5);
  Serial.println('A');
  Serial.flush(); // Wait for data to send
  delay(1000);

}