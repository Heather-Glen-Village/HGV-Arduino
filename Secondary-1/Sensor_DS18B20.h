#include <OneWire.h>
#include <DallasTemperature.h>
#include "conf.h"

OneWire oneWire(DS18B20_PIN);
DallasTemperature DS18B20(&oneWire);

// Function to initialize the sensor with a specified pin
void initializeDS18B20()
{
  DS18B20.begin();
}

// Function to get the temperature
float DS18B20_Temp(int index)
{
  DS18B20.requestTemperatures();
  float temp = DS18B20.getTempCByIndex(index); // asks for which sensors you want attached to the data wire (Starts at 0)
  return temp;
}
