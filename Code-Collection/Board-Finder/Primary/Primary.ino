#define LED 2

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
}

void loop(){
    digitalWrite(LED, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Primary Board Code - Blinking OFF");
    delay(500);
    digitalWrite(LED, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Primary Board Code - Blinking ON");
    delay(500);
}