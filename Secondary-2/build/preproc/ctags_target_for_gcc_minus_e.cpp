# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
# 2 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino" 2
# 3 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino" 2
# 4 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino" 2

// Pins List
# 15 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
// Defines the ID for the Secondary Board from 1-246


// Initialize Libaries
SoftwareSerial modbusSerial(17 /* A3*/, 16 /* A2*/);
ModbusRTUSlave modbus(modbusSerial, 9); // Create Modbus Object

bool coils[1] = {1};
uint16_t InputRegisters[1];


void setup() {
  pinMode(2, 0x1);

  modbus.configureCoils(coils, 1);
  modbus.configureInputRegisters(InputRegisters, 1);
  modbus.begin(2, 9600); // ID | Baud Rate
  Serial.begin(9600); // For Debuging
}

void loop() {
modbus.poll();
    if (coils[0] == 1) {
        coils[0] = 0;
        InputRegisters[0] = random(0, 65536);
        Serial.print("Changed to: "); // Debugging Line
        Serial.println(InputRegisters[0]);
    }
delay(500);
}
