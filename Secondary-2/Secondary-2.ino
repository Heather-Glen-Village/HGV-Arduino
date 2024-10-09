#define buzzerPin 2

void setup() {
  pinMode(buzzerPin, OUTPUT);  // Set buzzer pin as output

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
// Quater Note
  digitalWrite(buzzerPin, HIGH); 
  delay(272);                    
  digitalWrite(buzzerPin, LOW);  
  delay(272);
}

void loop() {
  // Empty loop, logic is in setup()
}
