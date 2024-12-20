# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
/*

  Secondary Sensors Sender



  The Skectch Made for Secondarys that collect Data from Sensors and Send them to the Priamry to be send to other locations.



  Pin List

    - D0 RX

    - D1 TX

    - D2 LED

    - D4 AM2302 Heat/DHT22

    - D5 SR-HC 50x Motion

    - D6 SW-1815P Vibration Sensor

    - D7 DS18B20 Heat

    - D14/A0 Water Leak Set 1 (Digital)

    - D15/A1 Water Leak Set 2 (Digital)

    - D18/A6 Water Leak Set 1 (Analog)

    - D19/A7 Water Leak Set 2 (Analog)



Coil Address Index

 - (0) Command to Read Sensors



Discrete Inputs Address Index 

 - (0) Motion Sensor

 - (1) Water Leak Sensor

 - (2) Smoke Data (From Primary)

 - (2) Vibration Sensor



Input Register/Float Register Address Index (InputRegister)[FloatRegister]

 - (0-1)[0] Temperature from DS18B20 

 - (2-5)[1-2] Temperature and Humidity from AM2302



  Created on November 11, 2024

  By Zachary Schultz

  Help from Arham Rashad For Sensor Code

*/
# 37 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino"
// Initializing libraries
# 39 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino" 2
# 40 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino" 2
# 41 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino" 2
# 42 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino" 2

//Importing .h files
# 45 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino" 2
# 46 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino" 2
# 47 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-2\\Secondary-2.ino" 2

//Modbus Arrays
bool Coils[1 /* Number of used Coil Address*/];
bool DiscreteInputs[4 /* Number of used Discrete Inputs Address*/];
uint16_t HoldingRegister[1 /* Number of used Holding Register Address*/];
uint16_t InputRegister[6 /* Number of used Input Register Address*/];
float *FloatRegister = (float*)InputRegister; // Turns an array of uint16 into floats by taking array in pairs

// Creating Modbus Connection
ModbusRTUSlave modbus(Serial /* Which Serial Is being Used*/); // No DERE Pins Used

void readDebug() {
      Serial.print("DS18B20 Temperature: ");
      Serial.println(DS18B20_Temp());
      Serial.print("AM2302 Temperature: ");
      Serial.println(AM2302_Temp());
      Serial.print("AM2302 Humidity: ");
      Serial.println(AM2302_Humidity());
      delay(10000);
}


void setup(){
  modbus.configureCoils(Coils,1 /* Number of used Coil Address*/);
  modbus.configureDiscreteInputs(DiscreteInputs,4 /* Number of used Discrete Inputs Address*/);
  modbus.configureHoldingRegisters(HoldingRegister,1 /* Number of used Holding Register Address*/);
  modbus.configureInputRegisters(InputRegister,6 /* Number of used Input Register Address*/);

  Serial.begin(9600);
  modbus.begin(2, 9600);

  initializeDS18B20();

  Serial.println("Secondary Board Sketch");
  Serial.print("Board ID: ");
  Serial.println(2);
  delay(1000);
}

void loop() {
  modbus.poll(); // Checks for changes
  if (Coils[0] == 1) { // Read Data Only When Primary Tells it To
    FloatRegister[0] = DS18B20_Temp();
    FloatRegister[1] = AM2302_Temp();
    FloatRegister[2] = AM2302_Humidity();

    DiscreteInputs[0] = 1;
    DiscreteInputs[1] = 1;
    DiscreteInputs[2] = 1;
    DiscreteInputs[3] = 0; //Always Zero As Primary Fills This in

    Coils[0] = 0; // Pervent Looping More then 1 Time
  }
  // else {
  //   readDebug();
  // }
  // delay(1000);
}
