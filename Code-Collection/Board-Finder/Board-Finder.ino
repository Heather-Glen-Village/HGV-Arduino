#define LED 2

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  digitalWrite(LED, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  if (Serial.available() > 0)  { 
    digitalWrite(LED, !digitalRead(LED));
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
  delay(500);
}
