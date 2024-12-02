# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
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
# 27 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
//Creating Modbus Connection
# 29 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino" 2
ModbusRTUSlave modbus(Serial); // No DERE Pins Used
# 40 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
bool discreteInputs[5 /* Amount of Sensors Using Discrete Inputs*/]; //Creates a 2d Array of NumSecondary rows for 4 Secondarys and DIColumns Columns 
// 0=Motion, 1=Water?, 2=... 
uint16_t InputRegister[6 /* Number of Input Register Column so Amount of Float Sensors Needed *2*/];
// 0-1=Temperature
float *FloatRegisters = (float*)InputRegister; // Turns an array of uint16 into floats by taking array in pairs
// 0=Tempature

//Modbus Arrays


void setup(){

}

void loop(){
}
