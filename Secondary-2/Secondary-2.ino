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
    digitalWrite(LED, DERE_POWER);
}

void loop(){
    digitalWrite(DERE, DERE_POWER);
    digitalWrite(LED, DERE_POWER);
    if (DERE_POWER == 1){
        delay(3000);
        Serial.print(Count);
        DERE_POWER = 0;
    }
    else if(Serial.available() != 0){
        Count = Serial.read();
        Serial.print("Got: ");
        Serial.println(Count);
        Serial.println('Sending: ');
        Count++;
        DERE_POWER = 1;
    }
    
}