# Secondary 1
In this Folder is all the code that is used in the all the Secondary Arduino, the Main file is the Secondary-1.ino with extra files used for organiztion and act like you just put all of the code into the Main file.
## What Each File Does
### Secondary-1.ino
is the Main file that Initializing all the Libraries Needed as well Importing all the code from the other files. From there it will initialize Modbus and all the used Sensors and then it will read the Sensors and send them to the Primary Arduino when it requests more Data.
### conf.h
This file contains all the information for the modules attached to the Arduino and their pin number so that in the Main Code you can Just right the Name of the Sensor and it will replace it with the right number. In the conf you can also find General Serial and Modbus configuration. Note the Modbus Array configuration should match the Modbus Array configuration in the Primary Conf.
### *_Sensor.h
This is all the Code for the Sensors that are attach to the Secondary. Each Sensors has it own file with code that is Made by other students and edited by Me to work with the Secondary.

## Note about Multiple Files
I Believed in C++ Coding this isn't the correct way to split code into multiple files but Its works for me, if you want to fix this then good luck.