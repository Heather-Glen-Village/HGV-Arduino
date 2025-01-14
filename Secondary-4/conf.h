// Defining Pins
#define LED 2
#define AM2302_PIN 4 // Also Known as DHT22
#define HC505_PIN 5
#define SW420_PIN 6
#define DS18B20_PIN 7
#define BME_CS 10
#define BME_MOSI 11
#define BME_MISO 12
#define BME_SCK 13
#define WL1D_PIN 14
#define WL2D_PIN 15
#define WL1A_PIN A6 // 18?
#define WL2A_PIN A7 // 19?

// Defining Variables for Sensors
// AM2302
#define AM2302_SensorType DHT22

// BME280
#define SEALEVELPRESSURE_HPA (1013.25) // Used Sea Levle Pressure to Estimate Altitude

// General Modbus Configuration
#define RS485Serial Serial // Which Serial Is being Used
#define baud 9600
#define ID 4 // Given Board ID

// Modbus Array Configuration <--(Should Match with Primary and other Secondarys)--/>

#define CoilAddress 1 // Number of used Coil Address
#define DIAddress 3   // Number of used Discrete Inputs Address
#define HRAddress 1   // Number of used Holding Register Address
#define IRAddress 14  // Number of used Input Register Address