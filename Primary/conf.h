// Defining Pins 
#define LED 2
#define Smoke 3
#define HeatON 4
#define WaterOFF 5
#define PowerOFF 6
#define CoolON 7

// Ethernet Configuration
#define MAC_ADDRESS {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF}
#define server { 192, 168, 3, 126 }


//MQTT Config
#define PrimaryNum 1 //Uused to Idenity Primary Might want to use Room Number Later
#define MQTTUser "arduino"
#define MQTTPassword "arduino"

#define SensorTopic "/sensor"
#define ArduinoCMD "/CMDArduino"
String TempRequest =  "/TempRequest/"+String(PrimaryNum);
String BootMessage = "Primary"+String(PrimaryNum)+" Is Online!";

// General Modbus Configuration
#define RS485Serial Serial // Which Serial Is being Used
#define baud 9600
#define NumSecondary 4 // Amount of Secondary Boards Being Used

// Modbus Array configuration (Should Match with Secondarys)

#define CoilAddress 1 // Number of used Coil Address
#define DIAddress 4 // Number of used Discrete Inputs Address
#define HRAddress 1 // Number of used Holding Register Address
#define IRAddress 8 // Number of used Input Register Addresss


