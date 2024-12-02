#include <Arduino.h>
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
/*
  Secondary Sensors Sender

  The Skectch Made for Secondarys that collect Data from Sensors and Send them to the Priamry to be send to other locations.

  Pin List
    - D0 RX
    - D1 TX
    - D2 LED
    - D3 
    - D4 
    - D5 
    - D6 
    - D7 
    - D8 
    - D9 
    - D10 
    - D11 
    - D12 
    - D13 

  Created on November 11, 2024
  By Zachary Schultz

*/

//Creating Modbus Connection
#include <ModbusRTUSlave.h>
ModbusRTUSlave modbus(Serial); // No DERE Pins Used




#define ID 1
#define LED 2

#define DIColumns 5 // Amount of Sensors Using Discrete Inputs
#define IRColumns 6 // Number of Input Register Column so Amount of Float Sensors Needed *2

bool discreteInputs[DIColumns]; //Creates a 2d Array of NumSecondary rows for 4 Secondarys and DIColumns Columns 
// 0=Motion, 1=Water?, 2=... 
uint16_t InputRegister[IRColumns];
// 0-1=Temperature
float *FloatRegisters = (float*)InputRegister; // Turns an array of uint16 into floats by taking array in pairs
// 0=Tempature

//Modbus Arrays


#line 50 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void setup();
#line 54 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void loop();
#line 50 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
void setup(){

}

void loop(){
}
