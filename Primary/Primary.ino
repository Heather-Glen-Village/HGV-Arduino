#include <SPI.h>
// SS/CS 10
// MOSI 11
// MISO 12
// SCK 13

int SlaveSelect = 10;

#include <SPI.h>

void setup() {
  Serial.begin(9600);
  SPI.begin();  // Initialize SPI
  pinMode(SlaveSelect, OUTPUT);  // Ensure SS is set as output
  digitalWrite(SlaveSelect, HIGH);  // Deselect the slave initially

  Serial.println("SPI test started");
}

void loop() {

  Serial.println(readVersionRegister());
  delay(1000);
}

byte readVersionRegister() {
  digitalWrite(SS, LOW);
  SPI.transfer(0x00);  // Send read instruction (use the correct register for your device)
  byte version = SPI.transfer(0x00);  // Receive version
  digitalWrite(SS, HIGH);
  return version;
}
