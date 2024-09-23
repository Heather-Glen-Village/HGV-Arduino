void setup()
{
    Serial.begin(9600);
    pinMode(13, OUTPUT);
}

void loop()
{
	digitalWrite(14, HIGH);
    Serial.println("High");
    delay(1000);
    digitalWrite(14, LOW);
    Serial.println("Low");
    delay(1000);
}
