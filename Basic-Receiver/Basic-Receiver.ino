//#define DI 0
//#define RO 1
#define LED 2
#define DERE 9
#define DERE_POWER LOW

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(DERE, OUTPUT);
    Serial.begin(9600);
    digitalWrite(DERE, DERE_POWER);
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