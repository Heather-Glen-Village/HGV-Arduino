# HGV Arduino
This Repository Covers all the Main Arduino Code Used in the HGV Project. The Arduino Code is split into 2 Folders with more details found in each.

### Primary
This portion of repository handles 3 majors tasks
- It uses Modbus to request Sensors data and storage its in a Json
-  It Communications with The Room to Change Room Tempature and other HVAC systems
-  Sends the Json to the Middleware System to be formated for other programs to use

#### Library used
- [SPI](https://docs.arduino.cc/learn/communication/spi/)
- [Ethernet](https://docs.arduino.cc/libraries/ethernet/) 
- [ModbusRTUMaster](https://github.com/CMB27/ModbusRTUMaster)
- [PubSubClient](https://github.com/knolleary/pubsubclient)
- [ArduinoJson](https://arduinojson.org/)
#### Hardware Needed
- RS485
- Ethernet Port

### Secondary
This portion of repository has only 1 Goal
- When Primary gives the signal, gather all the sensor data and send it back to the Primary over Modbus
#### Library used
- [ModbusRTUSlave](https://github.com/CMB27/ModbusRTUSlave/)
- [OneWire](https://docs.arduino.cc/libraries/onewire/)
- [DallasTemperature](https://docs.arduino.cc/libraries/dallastemperature/)
- [DHT](https://reference.arduino.cc/reference/en/libraries/dht-sensor-library/)
- [Wire](https://docs.arduino.cc/language-reference/en/functions/communication/wire/)
- [SPI](https://docs.arduino.cc/learn/communication/spi/)
- [Adafruit_Sensor](https://docs.arduino.cc/libraries/adafruit-unified-sensor/)
- [Adafruit_BME280](https://docs.arduino.cc/libraries/adafruit-bme280-library/)

#### Hardware Needed
- RS485
- AM2302
- BME280
- DS18B20
- HC505
- SW420

## Things Left to Work on

- Many of the Connections such as Ethernet or RS485 aren't Stable
- It Communications with The Room to Change Room Tempature and other HVAC systems hasn't be codded yet
- Any other sensors we want to add

## Project Flow Chart
![image](https://github.com/user-attachments/assets/66b08bec-683c-459b-b8fa-ee63cef260bb)
