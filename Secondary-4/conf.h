// Defining Pins 
#define LED 2
#define DHT22 4 //Also Known as AM2302
#define Motion 5
#define Vibration 6
#define DS18B20 7 // WE TESTING THIS ONE USB3
#define WL1D 14
#define WL2D 15
#define WL1A A6 //18?
#define WL2A A7 //19?

// General Modbus Configuration 
#define RS485Serial Serial // Which Serial Is being Used
#define baud 9600
#define ID 4

// Modbus Array configuration (Should Match with Primary)

#define CoilAddress 1 // Number of used Coil Address
#define DIAddress 5 // Number of used Discrete Inputs Address
#define HRAddress 1 // Number of used Holding Register Address
#define IRAddress 6 // Number of used Input Register Address