#define buzzerPin 2
const int ledPins[] = {0,1};

void setup() {
  pinMode(buzzerPin, OUTPUT);  // Set buzzer pin as output

  // Set LED pins as output
  for (int i = 0; i < 2; i++) { // fine I guess I feel like it a bit overkill you could just have 2 vars for 2 Leds
    pinMode(ledPins[i], OUTPUT);
  }

  // Quater Note
  digitalWrite(buzzerPin, HIGH); 
  delay(272);                    
  digitalWrite(buzzerPin, LOW);  
  delay(272);
  // 2 Eighth Notes
  digitalWrite(buzzerPin, HIGH); 
  delay(136);                    
  digitalWrite(buzzerPin, LOW);  
  delay(136);

  digitalWrite(buzzerPin, HIGH); 
  delay(136);                    
  digitalWrite(buzzerPin, LOW);  
  delay(136);
  // Quater Note
  digitalWrite(buzzerPin, HIGH); 
  delay(272);                    
  digitalWrite(buzzerPin, LOW);  
  delay(272);
  // Half Note
  digitalWrite(buzzerPin, HIGH); 
  delay(545);                    
  digitalWrite(buzzerPin, LOW);  
  delay(272);
  // 1 Quater Rest
delay(272);
  // Quater Note
  digitalWrite(buzzerPin, HIGH); 
  delay(272);                    
  digitalWrite(buzzerPin, LOW);  
  delay(272);
// Eigth Rest
  delay(136);
// Quater Note
  digitalWrite(buzzerPin, HIGH); 
  delay(272);                    
  digitalWrite(buzzerPin, LOW);  
  delay(272);
}

void loop() {
  // Empty loop, logic is in setup()
}
