//#define DI 0
//#define RO 1
#define LED 2
#define DERE 8

int DERE_POWER = 1; // Start Receiving
int Count = 0;

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(DERE, OUTPUT);
    Serial.begin(9600);

    digitalWrite(DERE, DERE_POWER);
    digitalWrite(LED, LOW);
}

void loop(){
    digitalWrite(DERE, DERE_POWER);
    //digitalWrite(LED, DERE_POWER);
    delay(1000);
    if (DERE_POWER == 1){
        Serial.println(Count);
        Serial.flush();
        DERE_POWER = 0;
    }
    else if(Serial.available() != 0){
        Count = Serial.parseInt();
        Serial.print("Got: ");
        Serial.println(Count);
        Serial.print("Sending: ");
        Count++;
        DERE_POWER = 1;
    }
}