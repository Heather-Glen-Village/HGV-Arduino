const int buzzerPin = 2;  // Buzzer connected to Pin 3

void setup() {
  pinMode(buzzerPin, OUTPUT);  // Set buzzer pin as output
}

void loop() {
  digitalWrite(buzzerPin, HIGH);  // Turn buzzer ON
  delay(1000);                    // Wait for 1 second (1000 ms)

  digitalWrite(buzzerPin, LOW);   // Turn buzzer OFF
  delay(1000);                    // Wait for 1 second (1000 ms)
}