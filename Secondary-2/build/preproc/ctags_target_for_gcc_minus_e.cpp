# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
# 2 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino" 2
# 3 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino" 2






# 8 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
// Pins List
// #define SoftTX 14 // Phyical TX 0
// #define SoftRX 15 // Phyical RX 1



// Defines the ID for the Secondary Board from 1-246


// Initialize Libaries
ModbusRTUSlave modbus(Serial, 9); // Create Modbus Object


//Modbus Data Types
bool coils[1];


// Sensor Code
float getTemperature() {
    // Read Temperature Sensor
    // return as a int? 
}
void setup()
{
    //Initialize Pins
    pinMode(2, 0x1);

    // Initialize Modbus
    modbus.configureCoils(coils, 1); // Says where The Coils can go and how many Value is allowed
    modbus.begin(2, 9600); // ID | Baud Rate
    //Initialize Serial
    Serial.begin(9600); // For Debuging
}

void loop()
{
    if (Serial.available() != 0) // Check if There been any Request
    {
        modbus.poll(); //act on the request from the Master
    }
    time_t t = now();
    Serial.println(t)
    delay(500); // Remove or lower at some point?
}
