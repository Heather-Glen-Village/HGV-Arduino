#include <Arduino.h>
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
#include <SPI.h>

const int CS_PIN = 10; // Adjust according to your wiring

#line 5 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void setup();
#line 20 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void loop();
#line 24 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void testSPI();
#line 5 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void setup() {
  Serial.begin(9600);
  
  // Set the CS pin as output
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);  // Ensure the SPI device is not selected (CS HIGH)
  
  // Initialize SPI
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);  // Set the SPI clock speed (optional)

  // Test SPI communication
  testSPI();
}

void loop() {
  // Nothing here
}

void testSPI() {
  Serial.println("Starting SPI test...");

  // Select the SPI device (CS low)
  digitalWrite(CS_PIN, LOW);
  
  // Send a test byte (e.g., 0x55) and read the response
  byte response = SPI.transfer(0x55);
  
  // Deselect the SPI device (CS high)
  digitalWrite(CS_PIN, HIGH);

  // Print the received response
  Serial.print("SPI Response: ");
  Serial.println(response, HEX);  // Print the response in hexadecimal
}

