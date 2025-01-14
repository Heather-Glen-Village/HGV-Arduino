#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "conf.h"

Adafruit_BME280 bme;

void initializeBME280()
{
    bme.begin();
}

float BME280_Temp()
{
    return bme.readTemperature();
}

float BME280_Humidity()
{
    return bme.readHumidity();
}

float BME280_Pressure()
{
    return bme.readPressure() / 100.0F;
}

float BME280_Altitude()
{
    return bme.readAltitude(SEALEVELPRESSURE_HPA);
}