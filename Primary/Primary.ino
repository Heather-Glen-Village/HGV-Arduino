#define DI 0
#define RO 1
#define LED 2
#define RsPower 8

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(RsPower, OUTPUT);
    Serial.begin(9600);
    digitalWrite(RsPower, LOW);
}

void loop(){
    if(Serial.available() > 0){
        String IncomingMessage = Serial.readString();
        Serial.println(IncomingMessage);
    }
}