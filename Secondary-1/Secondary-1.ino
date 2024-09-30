//#define DI 0
//#define RO 1
#define LED 2
#define DERE 8
const int DERE_POWER = 255;

void setup() {
    pinMode(LED, DERE_POWER);
    pinMode(DERE, OUTPUT);
    Serial.begin(9600);
    digitalWrite(DERE, LOW);
}

void loop(){
    if(Serial.available() > 0){
        String IncomingMessage = Serial.readString();
        Serial.print("Received: ");
        Serial.println(IncomingMessage);
        if(IncomingMessage == "Test") {
            digitalWrite(LED, !digitalRead(LED));
        }
    }
}