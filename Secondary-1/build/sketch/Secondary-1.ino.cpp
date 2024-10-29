#include <Arduino.h>
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
#include <DHT.h>
#include <ModbusRTUSlave.h>
const int MOTION_SENSOR_PIN = 5;

#define DEVICE_DISCONNECTED_C -1
#define DHTPIN 3      // Pin D3
#define DHTTYPE DHT22 // DHT 22 (AM2302)
#define DERE 9
#define ID 1

ModbusRTUSlave modbus(Serial, DERE);

bool coils[1];
uint16_t InputRegisters[6];
float *FloatRegisters = (float*)InputRegisters; 

int motionCurrentState = LOW; 
int motionPreviousState = LOW;

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

#line 23 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void setup();
#line 34 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void loop();
#line 23 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void setup() {

  modbus.configureCoils(coils, 1);
  modbus.configureInputRegisters(InputRegisters, 2);
  modbus.begin(ID,9600);
  Serial.begin(9600); // Start serial communication
  dht.begin();        // Initialize the DHT sensor
  pinMode(MOTION_SENSOR_PIN, INPUT); // Sensor is input
  pinMode(2, OUTPUT);
}

void loop() {
  if(Serial.available() !=0){
  modbus.poll();
  }  
  
  motionPreviousState = motionCurrentState;
  motionCurrentState = digitalRead(MOTION_SENSOR_PIN);
 if((motionCurrentState != DEVICE_DISCONNECTED_C)&&(motionPreviousState!= DEVICE_DISCONNECTED_C)){
  //Serial.println("lkjbeghjtg");    // Yup it works
 }
  if (motionPreviousState == LOW && motionCurrentState==HIGH){
  Serial.println("MOTION DETECTED!!");
  coils[0] = true;
  }

  if(motionPreviousState==HIGH && motionCurrentState==LOW){
  Serial.println("MOTION STOPPED.");
   coils[0] = false;
  }
  else {
    coils[0] = false; 
  }
  
  // Read temperature as Celsius
  float temperature = dht.readTemperature();
  // Read humidity
  float humidity = dht.readHumidity();

  FloatRegisters[0] = temperature;
  FloatRegisters[1] = humidity;

  // Check if any reads failed and exit early
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

Serial.println("Sensor readings: ");
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print(", Humidity: ");
  Serial.println(humidity);
   delay(2000); // Wait a few seconds between readings
  
}

 
