# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
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
# 27 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
//Creating Modbus Connection
# 29 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino" 2
ModbusRTUSlave modbus(Serial); // No DERE Pins Used

// Initializing Pins


// Modbus Settingss







//Modbus Arrays

bool Coils[1];

bool discreteInputs[5 /* Amount of Sensors Using Discrete Inputs*/]; //Creates a 2d Array of NumSecondary rows for 4 Secondarys and DIColumns Columns 
// 0=Motion, 1=Water?, 2=... 
uint16_t InputRegister[6 /* Number of Input Register Column so Amount of Float Sensors Needed *2*/];
// 0-1=Temperature
float *FloatRegisters = (float*)InputRegister; // Turns an array of uint16 into floats by taking array in pairs
// 0=Tempature

//Default Values

bool discreteInputs[] = {0,1,0,1,0};

float FloatRegisters[] = {1.22,2.22,3.22};


void setup(){
  modbus.configureCoils(Coils,1);
  modbus.configureDiscreteInputs(discreteInputs,5 /* Amount of Sensors Using Discrete Inputs*/);
  //modbus.configureHoldingRegisters();
  modbus.configureInputRegisters(InputRegister,6 /* Number of Input Register Column so Amount of Float Sensors Needed *2*/);

  Serial.begin(9600);
  modbus.begin(2, 9600);
}

void loop() {
  if (Serial.available() > 0) { //want to test if this isn't need anymore but that a later plan
    modbus.poll(); // Checks for changes
    if (Coils[0] == 1) {
      Coils[0] = 0;
      digitalWrite(2, !digitalRead(2));
    }
  }
}
