# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
# 2 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino" 2
# 3 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino" 2
// Pins List
# 13 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
// Defines the ID for the Secondary Board from 1-246


// Initialize Libaries
SoftwareSerial modbusSerial(17 /* A3*/, 16 /* A2*/);
ModbusRTUSlave modbus(modbusSerial, 9); // Create Modbus Object

bool coils[1] = {1};
uint16_t InputRegisters[2];
float *FloatRegisters = (float*)InputRegisters; // Usable Address is from 0-99? Temperature: 0-49, Humidity 50-99 

float floatArray[100] = {
    12.34, 45.67, 89.12, 34.56, 78.90, 23.45, 67.89, 12.34, 56.78, 90.12,
    34.56, 78.90, 23.45, 67.89, 12.34, 56.78, 90.12, 34.56, 78.90, 23.45,
    67.89, 12.34, 56.78, 90.12, 34.56, 78.90, 23.45, 67.89, 12.34, 56.78,
    90.12, 34.56, 78.90, 23.45, 67.89, 12.34, 56.78, 90.12, 34.56, 78.90,
    23.45, 67.89, 12.34, 56.78, 90.12, 34.56, 78.90, 23.45, 67.89, 12.34,
    56.78, 90.12, 34.56, 78.90, 23.45, 67.89, 12.34, 56.78, 90.12, 34.56,
    78.90, 23.45, 67.89, 12.34, 56.78, 90.12, 34.56, 78.90, 23.45, 67.89,
    12.34, 56.78, 90.12, 34.56, 78.90, 23.45, 67.89, 12.34, 56.78, 90.12,
    34.56, 78.90, 23.45, 67.89, 12.34, 56.78, 90.12, 34.56, 78.90, 23.45,
    67.89, 12.34, 56.78, 90.12, 34.56, 78.90, 23.45, 67.89, 12.34, 56.78
};
int16_t x = -1;

void setup()
{
  pinMode(2, 0x1);

  modbus.configureCoils(coils, 1);
  modbus.configureInputRegisters(InputRegisters, 2);
  modbus.begin(1, 19200); // ID | Baud Rate
  Serial.begin(9600); // For Debuging
}

void loop() {
modbus.poll();
    if (coils[0] == 1) {
        coils[0] = 0;
        if (x == 99) {
            x = 0;
        }
        else {
            x++;
        }
        FloatRegisters[0] = floatArray[x];
        Serial.println();
        Serial.println("----------------------------------------------------------------");
        Serial.print("InputRegisters 1: "); Serial.println(InputRegisters[0]);
        Serial.print("InputRegisters 2: "); Serial.println(InputRegisters[1]);
        Serial.print("Float Registers 1: "); Serial.println(FloatRegisters[0]);
    }
}
