# Primary

In this Folder is all the code that is used in the all the Primary Arduino, the Main file is the Primary.ino with extra files used for organization and act like you just put all of the code into the Main file.

## What Each File Does

### Primary.ino

is the Main file that Initializing all the Libraries Needed as well Importing all the code from the other files. From there it will initialize Modbus and MQTT and start the main loop. The Code will request Sensors data from all the Secondary Arduino Attach as well Sensor Attach to the Primary Board, from there it will send that information to NodeRed via MQTT then repeat after 5 Seconds. Later it will also receive messages and interact with the Room/RTA to set the Heater.

### conf.h

This file contains all the information for the modules attached to the Arduino and their pin number so that in the Main Code you can Just right the Name of the Sensor and it will replace it with the right number. In the conf you can also find General Serial Modbus,Ethernet, and MQTT configuration. Note the Modbus Array configuration should match the Modbus Array configuration in the Secondary Conf.

### mqtt.h

Is that code that is used to communicate with MQTT. It contains both the initialization for MQTT and also the ability to turn a 2D Array into a Json that can be send to NodeRed.

### json.h

Take Data gather from Secondary and Primary and formats into a Json that can be send to NodeRed

### errorcheck.h

This code will take an error code from the ModbusRTUMaster library and turn into something that I can understand

## Note about Multiple Files

I Believed in C++ Coding this isn't the correct way to split code into multiple files but Its works for me, if you want to fix this then good luck.
