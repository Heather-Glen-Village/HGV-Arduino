# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
# 2 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino" 2

# 4 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino" 2

// Pins List






ModbusRTUMaster modbus(Serial, 9); // Create Modbus Object with port for RS485

bool SlaveLED = 1; // Enable

void setup() {
  pinMode(2, 0x1);
  digitalWrite(2, SlaveLED);
  //modbus.setTimeout(500);
  modbus.begin(9600); // Baud Rate  | Config?
}

void loop() {
  if (modbus.writeSingleCoil(1, 0, SlaveLED) == 0) {
    SlaveLED = !SlaveLED;
  }
  digitalWrite(2, SlaveLED);
  delay(2000);
}
