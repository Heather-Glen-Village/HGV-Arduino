//#define DI 0
//#define RO 1
#define LED 2
#define RsPower 8

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(RsPower, OUTPUT);
    Serial.begin(9600);
    digitalWrite(RsPower, HIGH);
}

void loop(){
  Serial.println("T"); // send a message 
  Serial.flush(); // wait till Primary get the message
  delay(5000);
  
    

}