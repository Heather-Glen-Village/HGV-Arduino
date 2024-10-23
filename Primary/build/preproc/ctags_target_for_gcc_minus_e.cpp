# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
# 2 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino" 2

const int CS_PIN = 10; // Adjust according to your wiring

void setup() {
  Serial.begin(9600);

  // Set the CS pin as output
  pinMode(CS_PIN, 0x1);
  digitalWrite(CS_PIN, 0x1); // Ensure the SPI device is not selected (CS HIGH)

  // Initialize SPI
  SPI.begin();
  SPI.setClockDivider(0x05); // Set the SPI clock speed (optional)

  // Test SPI communication
  testSPI();
}

void loop() {
  // Nothing here
}

void testSPI() {
  Serial.println("Starting SPI test...");

  // Select the SPI device (CS low)
  digitalWrite(CS_PIN, 0x0);

  // Send a test byte (e.g., 0x55) and read the response
  byte response = SPI.transfer(0x55);

  // Deselect the SPI device (CS high)
  digitalWrite(CS_PIN, 0x1);

  // Print the received response
  Serial.print("SPI Response: ");
  Serial.println(response, 16); // Print the response in hexadecimal
}
