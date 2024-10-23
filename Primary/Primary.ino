#include <SPI.h>
// SS/CS 10
// MOSI 11
// MISO 12
// SCK 13

int SS = 10;

#include <SPI.h>

void setup() {
  Serial.begin(9600);
  SPI.begin();  // Initialize SPI
  pinMode(SS, OUTPUT);  // Ensure SS is set as output
  digitalWrite(SS, HIGH);  // Deselect the slave initially

  Serial.println("SPI test started");
}

void loop() {
  digitalWrite(SS, LOW);  // Select the slave

  // Send a byte (0xAA) and receive a byte
  byte receivedData = SPI.transfer(0xAA);

  digitalWrite(SS, HIGH);  // Deselect the slave

  // Print the received data
  Serial.print("Received: 0x");
  Serial.println(receivedData, HEX);

  delay(1000);
}