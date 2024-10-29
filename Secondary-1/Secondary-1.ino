#include <ModbusRTUSlave.h>
#include <SoftwareSerial.h>

// Pins List
#define SoftTX 16 // A2
#define SoftRX 17 // A3
#define LED 2
#define DHT22 4
#define Motion 5
#define Vibration 6
#define DS18B20 7
#define DERE 9

// Defines the ID for the Secondary Board from 1-246
#define ID 1

// Initialize Libaries
SoftwareSerial modbusSerial(SoftRX, SoftTX);
ModbusRTUSlave modbus(modbusSerial, DERE); // Create Modbus Object


//Modbus Data Types
bool DiscreteInputs[4]; 
uint16_t InputRegister[6]; // Temperature: 0-99, Humidity: 100-199, DHT22 Time: 200-299
float *FloatRegisters = (float*)InputRegister; // Usable Address is from 0-99? Temperature: 0-49, Humidity 50-99 



// Sensor Code
void getDHT22() {
    // Read DHT22 Sensor
    // return 2 floats?
    float DHT22Temp = 0.0;
    float DHT22Humidity = 0.0;
    FloatRegisters[0] = DHT22Temp;
    FloatRegisters[1] = DHT22Humidity;
}
void getDS18B20() {
  // Read DS18B20
  // Return as a float
  float DS18B20Temp = 0.0;
  FloatRegisters[2] = DS18B20Temp;
}
void getMotion() {
    // Read Motion Sensor
    // return true if motion detected, false otherwise
    bool MotionDetected = false;
    DiscreteInputs[0] = MotionDetected;
}

void getSmoke() {
  // Read Smoke Sensor
  // Returns a Bool
    bool SmokeDetected = false;
    DiscreteInputs[1] = SmokeDetected;
}
void getWaterLeak() {
  // Read WaterLeak
  // Returns Bool?
    bool WaterLeakDetected = false;
    DiscreteInputs[2] = WaterLeakDetected;
}
void getVibration() {
  // Read SW1815P for Vibration
  // returns a bool???? 
    bool VibrationDetected = false;
    DiscreteInputs[3] = VibrationDetected;
}

void setup() {
    //Initialize Pins
    pinMode(LED, OUTPUT);
    pinMode(DHT22, OUTPUT); //probably Not Needed
    pinMode(Motion, OUTPUT); //probably Not Needed
    pinMode(Vibration, INPUT); //?? idk if this right
    pinMode(DS18B20, OUTPUT); //probably Not Needed

    // Initialize Modbus Data Types
    modbus.configureDiscreteInputs(DiscreteInputs, 4);
    modbus.configureInputRegisters(InputRegister, 6);
             
    //Initialize Modbus and Serial Terminal
    modbus.begin(ID, 9600); 
    modbusSerial.begin(9600);
    Serial.begin(9600); // Debug only
}

void loop() {    
    if (Serial.available() != 0) { // Only Let it poll when something has been Sent Via Uart
      //Checks all Sensors
      getDHT22();
      getDS18B20();
  
      getMotion();
      getSmoke();
      getWaterLeak();
      getVibration();
      //Updates Modbus
      modbus.poll();

      Serial.println("----------------------------------------------------------------");
      Serial.println("DHT22 Temp: "+String(FloatRegisters[0]));
      Serial.println("DHT22 Humidity: "+String(FloatRegisters[1]));
      Serial.println("DS18B20 Temp: "+String(FloatRegisters[2]));  
      Serial.println();
      Serial.println("Motion: "+String(DiscreteInputs[0]));
      Serial.println("Smoke: "+String(DiscreteInputs[1]));
      Serial.println("WaterLeak: "+String(DiscreteInputs[2]));
      Serial.println("Vibration: "+String(DiscreteInputs[3]));


    }
    delay(500);
}