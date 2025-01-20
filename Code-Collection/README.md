# Code Collection
This folder contains a collection of old code for Arduino that were made mainly for the purpose of testing 1 part of the system at the time. Most code isn't really made to be used ina  real project and is just here for testing purposes. you can use some of it as a base for creating your own code just note not everything is working 100%.

## Directory
### ArduinoJsontest
Is testing the ArduinoJson Library Printing it out into the Serial Terminal 
### Basic-RS485
using just Basic Serial communication, it test if a RS485 Connection is working by having one code send a message in the Serial Terminal and another see if it can receive a message.
### Board-Finder 
is some code used to locate which board is what USB ID by having the LED Flash when Typing Messageing into the Serial Terminal. Orginal it was made for each board to have it own code but it was changed to have all board using the same code (Board-Finder.ino)
### Ethernet
Just a basic test to see if your able to get an Arduino Board to obtain a Static IP.
### Modbus
A bunch of different Modbus Code testing a bunch of different situation. the Code split into 2 parts, Master which send Messages and Slaves which receive Messages.
### MQTT
Testing MQTT using the PubSubClient Library 
### Relaytest
Testing if I was able to change a Relay which made it so another 2 board could or couldn't Commuitate with RS485 (Don't Believe it every work due to Hardware)
### system-checks
Basic Code to test if most of the major systems are working such as Modbus and all major Secondary Sensors
