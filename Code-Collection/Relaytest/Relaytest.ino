#define LED 2
#define RelayPin 3

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  pinMode(RelayPin, OUTPUT);
  digitalWrite(RelayPin, LOW);
  while (!Serial);
  Serial.println("Relay Board START!");
  delay(1000);

  Serial.println("Enter A String into the Serial Terminal to Switch Modbus");
  digitalWrite(LED, LOW);
  digitalWrite(LED_BUILTIN, LOW);

}

void loop() {
  
  if (Serial.available() > 0)  {
    Serial.readString();
    digitalWrite(LED, !digitalRead(LED));
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    digitalWrite(RelayPin, !digitalRead(RelayPin));
    if(digitalRead(RelayPin) == HIGH) {
        Serial.println("Now in Upload Mode!");
    }
    else {
        Serial.println("Now in Prodution Mode!");
    }
  }
  delay(2000);
}
