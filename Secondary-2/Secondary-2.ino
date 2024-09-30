//#define DI 0
//#define RO 1
#define LED 2
#define DERE 8
#define DERE_POWER LOW

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(DERE, OUTPUT);
    Serial.begin(9600);
    digitalWrite(DERE, DERE_POWER);
}

void loop(){
    if(Serial.available() > 0){
        int IncomingMessage = Serial.parseInt();
        Serial.print("Received: ");
        Serial.println(IncomingMessage);
      	Serial.println(IncomingMessage+1);
        if(IncomingMessage == 2) {
            digitalWrite(LED, !digitalRead(LED));
        }
    }
}