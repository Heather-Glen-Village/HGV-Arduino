//#define DI 0
//#define RO 1
#define LED 2
#define RsPower 8

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(RsPower, OUTPUT);
    Serial.begin(9600);
}

void loop(){
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
}