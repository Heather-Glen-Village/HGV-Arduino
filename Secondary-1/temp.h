


OneWire oneWire(DS18B20);
DallasTemperature DS18B20(&oneWire);

void setup() {
  Serial.begin(115200);
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