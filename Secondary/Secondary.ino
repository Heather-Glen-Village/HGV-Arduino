#define LED 2

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  digitalWrite(LED, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Board Finder Started!");
  Serial.println("Press Enter into the Terminal to Switch LED");
  Serial.println("Enter Character To cause the LED to Flash");
}

void loop() {
  
  if (Serial.available() > 0)  {
    Serial.read();
    digitalWrite(LED, !digitalRead(LED));
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    if(digitalRead(LED) == HIGH) {
        Serial.println("LED is Now Enabled");
    }
    else {
        Serial.println("LED is Now Disable");
    }
  }
  delay(500);
}
