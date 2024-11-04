#define LED 2

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    Serial.println("Secondary-2 Board Code - OFF");
    digitalWrite(LED, LOW);
    digitalWrite(LED_BUILTIN, LOW);
}

void loop(){
}