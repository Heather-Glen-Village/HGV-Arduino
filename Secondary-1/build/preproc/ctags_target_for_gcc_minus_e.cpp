# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
# 2 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino" 2

// Pins List
// #define SoftTX 14 // Phyical TX 0
// #define SoftRX 15 // Phyical RX 1



// Defines the ID for the Secondary Board from 1-246


// Initialize Library
ModbusRTUSlave modbus(Serial, 9); // Create Modbus Object

bool coils[1]; // Creating an array where the Coils can go | Read & Write Only Bools

void setup()
{
  pinMode(2, 0x1);

  modbus.configureCoils(coils, 1); // Says where The Coils can go and how many Value is allowed
  modbus.begin(1, 9600); // ID | Baud Rate
  Serial.begin(9600); // For Debuging
}

void loop()
{
  if (modbus != 0) // Check if There been any Request
  {
    Serial.println("LED Change"); // Debugging Line
    modbus.poll(); // Check and act on the request from the Master

    digitalWrite(2, coils[0]); // Changes LED to Match with new Message
  }

  delay(500);
}
