// Defining Pins 
#define LED 2
#define Smoke 3
#define HeatON 4
#define WaterOFF 5
#define PowerOFF 6
#define CoolON 7

// Ethernet Configuration
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF}; //Used Mac Address
// This stuff Might Not be Need if Using MQTT
#define StaticIP { 192, 168, 3, 168 } 
#define Submask { 255, 255, 255, 0 }
#define Gateway { 192, 168, 3, 1 }
#define DNS { 192, 168, 3, 1 } 

// General Modbus Configuration
#define RS485Serial Serial // Which Serial Is being Used
#define baud 9600
#define NumSecondary 4 // Amount of Secondary Boards Being Used

// Modbus Array configuration (Should Match with Secondarys)

#define CoilAddress 1 // Number of used Coil Address
#define DIAddress 5 // Number of used Discrete Inputs Address
#define HRAddress 1 // Number of used Holding Register Address
#define IRAddress 6 // Number of used Input Register Addresss