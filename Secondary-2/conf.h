// Defining Pins 
#define LED 2
#define AM2302_PIN 4 //Also Known as DHT22
#define Motion_PIN 5
#define Vibration_PIN 6
#define DS18B20_PIN 7
#define WL1D_PIN 14
#define WL2D_PIN 15
#define WL1A_PIN A6 //18?
#define WL2A_PIN A7 //19?

// General Modbus Configuration 
#define RS485Serial Serial // Which Serial Is being Used
#define baud 9600
#define ID 2

// Modbus Array configuration (Should Match with Primary)


#define CoilAddress 1 // Number of used Coil Address
#define DIAddress 4 // Number of used Discrete Inputs Address
#define HRAddress 1 // Number of used Holding Register Address
#define IRAddress 6 // Number of used Input Register Address