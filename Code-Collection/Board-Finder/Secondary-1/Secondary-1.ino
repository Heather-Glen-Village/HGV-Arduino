#define LED 2

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    digitalWrite(LED, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop(){
    Serial.println("Secondary-1 Board Code - ON");
    delay(1000);
}