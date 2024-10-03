//#define DI 0
//#define RO 1
#define LED 2
#define DERE 9

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(DERE, OUTPUT);
    Serial.begin(9600);
}

void loop(){
    digitalWrite(LED, HIGH);
    Serial.println("Secondary-2 Board Code");
    delay(1000);
    digitalWrite(LED, LOW);
    delay(1000);
    Serial.println("Secondary-2 Board Code");
}