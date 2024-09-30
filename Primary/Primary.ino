//#define DI 0
//#define RO 1
#define LED 2
#define DERE 8
#define DERE_POWER HIGH
int Count = 0;
void setup() {
    pinMode(LED, OUTPUT);
    pinMode(DERE, OUTPUT);
    Serial.begin(9600);
    
    digitalWrite(DERE, DERE_POWER);
    digitalWrite(LED, HIGH);
}

void loop(){
  Serial.print(Count++); // send a message 
  Serial.flush(); // wait till Primary get the message
  delay(5000);
}