// Defining Pins 
#define LED 2
#define Smoke_PIN 3
#define HeatON 4
#define WaterOFF 5
#define PowerOFF 6
#define CoolON 7

// Ethernet/MQTT Broker Configuration
#define MAC_ADDRESS {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF} 
#define server { 192, 168, 3, 126 } // IP Address of MQTT Broker Running on REMS006
#define port 1883


//MQTT Config
#define PrimaryNum 1 //Used to Idenity Primary Might want to use Room Number Later
#define MQTTUser "arduino"
#define MQTTPassword "arduino"

#define SensorTopic "/sensors" //topic all Sensor Json get sent to
#define ArduinoCMD "/CMDArduino" //currently unused
#define temprequest "/temprequest/" 
#define bootmessage "/bootmessage"

// General Modbus Configuration
#define RS485Serial Serial1 // Which Serial Is being Used
#define baud 9600
#define NumSecondary 1 // Amount of Secondary Boards Being Used

// Modbus Array configuration <--(Should Match with Secondarys)--/>

#define CoilAddress 1 // Number of used Coil Address
#define DIAddress 3 // Number of used Discrete Inputs Address
#define HRAddress 1 // Number of used Holding Register Address
#define IRAddress 6 // Number of used Input Register Addresss


