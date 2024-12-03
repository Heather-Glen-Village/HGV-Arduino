# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
# 2 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino" 2
# 3 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino" 2



OneWire oneWire(7);
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
  Serial.println(temp);
  // if (temp == DEVICE_DISCONNECTED_C) {
  //   Serial.println("ERROR");
  // }
  // else {
  //   Serial.print(temp);
  //   Serial.println(" °C");
  // }
  delay(2000);
}
