#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 7

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

void setup() {
  Serial.begin(9600);
  DS18B20.begin();
  delay(2000);
}

void loop() {
  DS18B20.requestTemperatures();
  Serial.print("DS18B20 Temperature: ");
  float temp = DS18B20.getTempCByIndex(0);
  if (temp == DEVICE_DISCONNECTED_C) {
    Serial.println("ERROR");
  }
  else {
    Serial.print(temp);
    Serial.println(" °C");
  }
  delay(2000);
}
