#define DI 0
#define RO 1
#define LED 2
#define RsPower 8

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(RsPower, OUTPUT);
    Serial.begin(9600);
    digitalWrite(RsPower, HIGH);
}

void loop(){
  Serial.println("----------------------------------------------------------------");
  Serial.println("Power Check");
  Serial.print("RsPower: ");
  Serial.println(digitalRead(RsPower));
  Serial.print("LED: ");
  Serial.println(digitalRead(LED));
  Serial.print("DI: ");
  Serial.println(1);
  Serial.print("RO: ");
  Serial.println(0);
  delay(5000);
  
    

}