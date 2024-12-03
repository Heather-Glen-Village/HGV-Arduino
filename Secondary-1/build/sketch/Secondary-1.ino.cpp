#include <Arduino.h>
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 7

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

#line 9 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void setup();
#line 15 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void loop();
#line 9 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
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

