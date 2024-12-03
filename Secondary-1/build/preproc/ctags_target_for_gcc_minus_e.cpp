# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
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



  Created on November 11, 2024

  By Zachary Schultz



*/
# 24 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
// Initializing libraries
# 26 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino" 2
# 27 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino" 2
# 28 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino" 2

//Importing .h files
# 31 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino" 2

//Modbus Arrays
bool Coils[1 /* Number of used Coil Address*/];
bool DiscreteInputs[5 /* Number of used Discrete Inputs Address*/] = {1,0,0,0,1};
uint16_t HoldingRegister[1 /* Number of used Holding Register Address*/];
uint16_t InputRegister[6 /* Number of used Input Register Address*/] = {1.11,2.11,3.11};
float *FloatRegisters = (float*)InputRegister; // Turns an array of uint16 into floats by taking array in pairs

// Creating Modbus Connection
ModbusRTUSlave modbus(Serial /* Which Serial Is being Used*/); // No DERE Pins Used

void setup(){
  modbus.configureCoils(Coils,1 /* Number of used Coil Address*/);
  modbus.configureDiscreteInputs(DiscreteInputs,5 /* Number of used Discrete Inputs Address*/);
  modbus.configureHoldingRegisters(HoldingRegister,1 /* Number of used Holding Register Address*/);
  modbus.configureInputRegisters(InputRegister,6 /* Number of used Input Register Address*/);

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
