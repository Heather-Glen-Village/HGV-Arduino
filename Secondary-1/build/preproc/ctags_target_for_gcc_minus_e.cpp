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

// Initializing Pins


// Modbus Settingss
# 43 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
//Modbus Arrays

bool Coils[1];

bool DiscreteInputs[5 /* Amount of Sensors Using Discrete Inputs*/] = {1,0,0,0,1};
// 0=Motion, 1=Water?, 2=... 
uint16_t HoldingRegister[1];
uint16_t InputRegister[6 /* Number of Input Register Column so Amount of Float Sensors Needed *2*/] = {1.11,2.11,3.11};
// 0-1=Temperature
float *FloatRegisters = (float*)InputRegister; // Turns an array of uint16 into floats by taking array in pairs
// 0=Tempature

void setup(){
  modbus.configureCoils(Coils,1);
  modbus.configureDiscreteInputs(DiscreteInputs,5 /* Amount of Sensors Using Discrete Inputs*/);
  modbus.configureHoldingRegisters(HoldingRegister,1);
  modbus.configureInputRegisters(InputRegister,6 /* Number of Input Register Column so Amount of Float Sensors Needed *2*/);

  Serial.begin(9600);
  modbus.begin(1, 9600);

  Serial.println("Secondary Board Sketch");
  Serial.print("Board ID: ");
  Serial.println(1);
  delay(1000);
}

void loop() {
  if (Serial.available() > 0) { //want to test if this isn't need anymore but that a later plan
    modbus.poll(); // Checks for changes
    if (Coils[0] == 1) {
      Coils[0] = 0;
      digitalWrite(2, !digitalRead(2));
      Serial.println("LED Changed");
    }
    Serial.print("Holding Register: ");
    Serial.println(HoldingRegister[0]);
  }
}
