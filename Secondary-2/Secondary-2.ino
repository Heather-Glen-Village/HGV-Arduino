void setup()
{
    Serial.begin(9600);
    pinMode(2, OUTPUT);
}

void loop()
{
	digitalWrite(14, HIGH);
    Serial.println("High");
    delay(1000);
    digitalWrite(2, LOW);
    Serial.println("Low");
    delay(1000);
}
