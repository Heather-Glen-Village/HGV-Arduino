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
    Serial.println(Count);
}

void loop(){
    while(Serial.available() == 0){
        digitalWrite(DERE, LOW);
        digitalWrite(LED, LOW);
    }
    Count = Serial.read();
    Serial.print("Received: ");
    Serial.println(Count);
    Count++;
    digitalWrite(LED, HIGH);
    delay(5000);
    Serial.print("Sending: ");
    digitalWrite(DERE, HIGH);
    Serial.println(Count);
    Serial.flush();
}