#define LED 2

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    Serial.println("Primary Board Code - Blinking");
}

void loop(){
    digitalWrite(LED, LOW);
    digitalWrite(LED_BUILTIN, LOW);

    delay(500);
    digitalWrite(LED, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
}