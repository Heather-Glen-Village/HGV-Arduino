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

// Initializing libraries
#include <ModbusRTUSlave.h>

//Importing .h files
#include "conf.h"


uint16_t test[4][6] = 
{{5243, 16270, 2621, 16391, 2621, 16455},
{10486, 16284, 5243, 16398, 5243, 16462},
{15729, 16298, 7864, 16405, 7864, 16469},
{20972, 16312, 10486, 16412, 10486, 16476}};

uint16_t test2[6] = {5243, 16270, 2621, 16391, 2621, 16455};

float (*Floattest) = (float(*))test;

//Row Col

void setup(){
  while (!Serial);
  Serial.begin(9600);
  for (int i = 0; i < 4; i++)
  {
   Serial.println(test[i][0]);
   Serial.println(test[i][1]);
   Serial.println(test[i][2]);
   Serial.println(test[i][3]);
   Serial.println(test[i][4]);
   Serial.println(test[i][5]); 
   Serial.println("-------------");
   Serial.println(Floattest[0]);
   Serial.println(Floattest[1]);
   Serial.println(Floattest[2]);
   Serial.println("-------------");
  }
  

}


void loop(){

}






// //Modbus Arrays
// bool Coils[CoilAddress];
// bool DiscreteInputs[DIAddress];
// uint16_t HoldingRegister[HRAddress];
// uint16_t InputRegister[IRAddress];
// float *FloatRegister = (float*)InputRegister; // Turns an array of uint16 into floats by taking array in pairs
// uint16_t LastHolding = HoldingRegister[0];

// // Creating Modbus Connection
// ModbusRTUSlave modbus(RS485Serial); // No DERE Pins Used

// void setup(){
//   modbus.configureCoils(Coils,CoilAddress);
//   modbus.configureDiscreteInputs(DiscreteInputs,DIAddress);
//   modbus.configureHoldingRegisters(HoldingRegister,HRAddress);
//   modbus.configureInputRegisters(InputRegister,IRAddress);

//   Serial.begin(baud);
//   modbus.begin(ID, baud);

//   Serial.println("Secondary Board Sketch");
//   Serial.print("Board ID: "); 
//   Serial.println(ID);
//   delay(1000);

//   //test data
//   DiscreteInputs[0] = 0;
//   DiscreteInputs[1] = 0;
//   DiscreteInputs[2] = 0;
//   DiscreteInputs[3] = 1;
//   DiscreteInputs[4] = 1;

//   FloatRegister[0] = 1.33f;
//   FloatRegister[1] = 2.33f;
//   FloatRegister[2] = 3.33f;
// }

// void loop() {    
//   modbus.poll(); // Checks for changes
//   if (Coils[0] == 1) {
//     Coils[0] = 0;
//     digitalWrite(LED, !digitalRead(LED));
//     Serial.println("Coil Changed");
//   }
//   if (LastHolding = HoldingRegister[0]) {
//     Serial.print("Holding Register Changed: ");
//     Serial.println(HoldingRegister[0]);
//     LastHolding = HoldingRegister[0];
//   }
// }