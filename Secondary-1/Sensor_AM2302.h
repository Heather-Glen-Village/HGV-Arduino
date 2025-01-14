#include <DHT.h>
#include "conf.h"

DHT AM2302(AM2302_PIN, AM2302_SensorType);

// Function to initialize the sensor with a specified pin
void initializeAM2302()
{
  AM2302.begin();
}

// Function to get the temperavture
float AM2302_Temp()
{
  return AM2302.readTemperature();
}

// Function to get the Humidity
float AM2302_Humidity()
{
  return AM2302.readHumidity();
}
