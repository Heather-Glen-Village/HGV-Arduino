#include <DHT.h>
#include "conf.h"

DHT AM2302(AM2302_PIN, DHT22);

// Function to initialize the sensor with a specified pin
void initializeAM2302() {
    AM2302.begin();
}

// Function to get the temperavture
float AM2302_Temp() {  
  float temp = AM2302.readTemperature();
  return temp;
}

// Function to get the Humidity
float AM2302_Humidity() {
  float humidity = AM2302.readHumidity();
  return humidity;
}
