# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
# 2 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino" 2
# 3 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino" 2

// Pins List





// Initialize Library
//SoftwareSerial modbusSerial(SoftRX, SoftTX);
ModbusRTUMaster modbus(Serial, 9); // Create Modbus Object with port for RS485

bool SlaveLED = 1; // Enable Slave LED by default

void setup()
{
  pinMode(2, 0x1);

  modbus.begin(9600);
  Serial.begin(9600); // For Debuging
}

void loop()
{
  digitalWrite(2, SlaveLED); // Matches Slave LED With Board LED

  modbus.writeSingleCoil(0, 0, SlaveLED); // 0 sends to all boards
  if (SlaveLED == 1)
  { // Turns LED off if on and vice versa
    SlaveLED = 0;
    Serial.println("SlaveLED Enabled");
  }
  else
  {
    SlaveLED = 1;
    Serial.println("SlaveLED Disabled");
  }
  delay(2000);
}
