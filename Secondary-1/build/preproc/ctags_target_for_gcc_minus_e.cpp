# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
# 2 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino" 2


// Pins List
// #define SoftTX 14 // Phyical TX 0
// #define SoftRX 15 // Phyical RX 1



// Defines the ID for the Secondary Board from 1-246
const uint16_t ID = 1;

// Initialize Libaries
ModbusRTUSlave modbus(Serial, 9); // Create Modbus Object


//Modbus Data Types
bool Coils[1];

uint16_t HoldingRegister[2]; // Temperature: 0-99, Humidity: 100-199, DHT22 Time: 200-299
float *FloatRegisters = (float*)HoldingRegister; // Usable Address is from 0-99? Temperature: 0-49, Humidity 50-99 

uint16_t InputRegister[200];
uint32_t *TimeRegisters = (uint32_t*)HoldingRegister; //Current uint which can do 16 Year of time data which is overkill but idk how time is being stored yet
//Usable Address Temp and Humidity: 100-149, Motion: 

bool newNumber = true;


//float floatlist = {0.1, 0.2, 0.3, 0.4, 0.5};


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
    modbus.configureCoils(Coils,1);
    modbus.configureInputRegisters(HoldingRegister, 2);
    //modbus.configureInputRegisters(InputRegister, 100);
    modbus.begin(ID, 9600); // ID | Baud Rate
    //Initialize Serial
    Serial.begin(9600); // For Debuging
    FloatRegisters[0] = 1.5f;
    Serial.println(FloatRegisters[0]);
    Serial.println(HoldingRegister[0]);
    Serial.println(HoldingRegister[1]);
}

void loop()
{
    /*if (newNumber == true) {

        for(int i = 0; i <= 10; i++) {

            FloatRegisters[i] = random(0, 10000) /100.0;

            Serial.println(HoldingRegister[i]);

        }

        newNumber = false;

        Serial.println("Done!");*/
# 65 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
    if (Serial.available() != 0) { // Check if There been any Request
        //act on the request from the Master
        modbus.poll();

        FloatRegisters[0] = random(0, 10000) /100.0f;
        Serial.println(FloatRegisters[0]);
        Serial.println(HoldingRegister[0]);
        Serial.println(HoldingRegister[1]);
    }

    delay(500); // Remove or lower at some point?
}
