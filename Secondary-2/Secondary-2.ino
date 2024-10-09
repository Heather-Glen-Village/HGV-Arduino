#define buzzerPin 2
const int ledPins[] = {0,1};

void setup() {
  pinMode(buzzerPin, OUTPUT);  // Set buzzer pin as output

  // Set LED pins as output
  for (int i = 0; i < 2; i++) { // fine I guess I feel like it a bit overkill you could just have 2 vars for 2 Leds
    pinMode(ledPins[i], OUTPUT);
  }

  // Signal the start of sequence
  digitalWrite(buzzerPin, HIGH);  // Turn buzzer ON
  delay(1000);                     // Beep for 500 ms
  digitalWrite(buzzerPin, LOW);   // Turn buzzer OFF
  delay(750);                     // Wait for 250 ms

  // Start of LED and wiring check sequence
  for (int i = 0; i < 2; i++) {
  digitalWrite(buzzerPin, HIGH);  // Turn buzzer ON (Shave note)
  delay(600);                     // Extended timing after "Shave"
  digitalWrite(buzzerPin, LOW);   // Turn buzzer OFF
  delay(500);

  digitalWrite(buzzerPin, HIGH);  // Turn buzzer ON
  delay(400);                     // Short note
  digitalWrite(buzzerPin, LOW);   // Turn buzzer OFF
  delay(500);

  digitalWrite(buzzerPin, HIGH);  // Turn buzzer ON
  delay(400); 
  digitalWrite(buzzerPin, LOW);   // Turn buzzer OFF
  delay(500);

  digitalWrite(buzzerPin, HIGH);  // Turn buzzer ON
  delay(400);
  digitalWrite(buzzerPin, LOW);   // Turn buzzer OFF
  delay(500);

  digitalWrite(buzzerPin, HIGH);  // Long buzz (Buzz)
  delay(250);
  digitalWrite(buzzerPin, LOW);   // Turn buzzer OFF
  delay(400);

  digitalWrite(buzzerPin, HIGH);  // Long buzz (Buzz)
  delay(300);
  digitalWrite(buzzerPin, LOW);   // Turn buzzer OFF
  delay(400);

  digitalWrite(buzzerPin, HIGH);  // Long buzz (Buzz)
  delay(350);
  digitalWrite(buzzerPin, LOW);   // Turn buzzer OFF
  delay(400);

  digitalWrite(buzzerPin, HIGH);  // Long buzz (Buzz)
  delay(600);
  digitalWrite(buzzerPin, LOW);   // Turn buzzer OFF
  }
}

void loop() {
  // Empty loop, logic is in setup()
}
