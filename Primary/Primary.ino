//#define DI 0
//#define RO 1
#define LED 2
#define DERE 8

int DERE_POWER = 0; // Start Sending
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

    if(Serial.available() > 0){ // Receiver Code
        int Count = Serial.parseInt();
        Serial.print("Received: ");
        Serial.println(Count);
        DERE_POWER = 1;
        delay(1000);
    }
    else if (DERE_POWER == 1){  // Sender Code
        Serial.println(Count+1); // send a message 
        Serial.flush(); // wait till other board get the message
        DERE_POWER = 0;
    }
    
}