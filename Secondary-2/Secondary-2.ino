//#define DI 0
//#define RO 1
#define LED 2
#define DERE 8

int DERE_POWER = 1; // Start Sending
int Count = 0;

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(DERE, OUTPUT);
    Serial.begin(9600);

    digitalWrite(DERE, DERE_POWER);
    digitalWrite(LED, DERE_POWER);
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