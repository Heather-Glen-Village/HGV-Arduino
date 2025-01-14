// defining Pins
#define AM2302_PIN 4
#define HC505_PIN 5
#define SW420_PIN 6
#define DS18B20_PIN 7

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1012.7)

#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

DHT AM2302(AM2302_PIN, DHT22);
OneWire oneWire(DS18B20_PIN);
DallasTemperature DS18B20(&oneWire);

Adafruit_BME280 bme;

void setup()
{
    Serial.begin(9600);
    pinMode(HC505_PIN, INPUT);
    pinMode(SW420_PIN, INPUT);
    AM2302.begin();
    DS18B20.begin();

    unsigned status = bme.begin(0x76);

    Serial.println("Mega Sensor Test");
}

// Reading Pin
void loop()
{
    Serial.println("===============================================================================");
    Serial.print("HC505: ");
    Serial.println(digitalRead(HC505_PIN));
    Serial.print("SW420: ");
    Serial.println(digitalRead(SW420_PIN));
    Serial.print("AM2302 Temp: ");
    Serial.println(AM2302.readTemperature());
    Serial.print("AM2302 Humidity: ");
    Serial.println(AM2302.readHumidity());
    Serial.print("DS18B20-1 Temp: ");
    Serial.println(DS18B20.getTempCByIndex(0));
    Serial.print("DS18B20-2? Temp: ");
    Serial.println(DS18B20.getTempCByIndex(1));
    Serial.print("BME Temp: ");
    Serial.println(bme.readTemperature());
    Serial.print("BME Humidity: ");
    Serial.println(bme.readHumidity());
    Serial.print("BME Pressure: ");
    Serial.println(bme.readPressure() / 100.0F);
    Serial.print("BME Altitude: ");
    Serial.println(bme.readAltitude(SEALEVELPRESSURE_HPA));
    delay(2000);
}