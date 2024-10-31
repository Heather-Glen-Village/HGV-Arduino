# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
# 2 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino" 2
# 3 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino" 2
# 4 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino" 2
// Pins List
# 14 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
// Defines the ID for the Secondary Board from 1-246


// Initialize Libaries
SoftwareSerial modbusSerial(15 /* A3*/, 14 /* A2*/); // RX TX
ModbusRTUMaster modbus(modbusSerial, 9); // Create Modbus Object

bool coils[1] = {1};
uint16_t InputRegisters[1];


void setup() {
  modbus.begin(9600);
  Serial.begin(9600); // For Debuging
  delay(5000); // For Debuging
}

void loop() {
Serial.println(modbus.writeSingleCoil(1,0,1));
delay(3000);
Serial.println(modbus.readInputRegisters(1, 0, InputRegisters,1));
Serial.print("InputRegisters: "); Serial.println(InputRegisters[0]);
delay(1000);
}
