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

#include <ArduinoRS485.h>
#include <ArduinoModbus.h>

#define ID 1
#define LED 2
#define Float 1.532


uint16_t PreFloat[2];
float *FloatRegisters = (float*)PreFloat;

void setup(){
  Serial.begin(9600);
  Serial.println("Secondary-1 Board Sketch");


  // start the Modbus RTU client
  RS485.setPins(1,0,-1);
  
  if (!ModbusRTUServer.begin(ID,9600)) {
    
    while (true)
    {
      Serial.println("Failed to start Modbus RTU Server!");
    }
    
  }

  FloatRegisters[0] = Float;

  ModbusRTUServer.configureCoils(0,1);
  ModbusRTUServer.configureDiscreteInputs(0,3);
  ModbusRTUServer.discreteInputWrite(0,ID);
  ModbusRTUServer.discreteInputWrite(1,PreFloat[0]);
  ModbusRTUServer.discreteInputWrite(2,PreFloat[1]);

  
}


void loop() {
  // poll for Modbus RTU requests
  int packetReceived = ModbusRTUServer.poll();

  if(packetReceived) {
    // read the current value of the coil
    bool coilValue = ModbusRTUServer.coilRead(0x00);
  
    if (coilValue == 1) {
      // coil value set, turn LED on
      digitalWrite(LED, HIGH);
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      // coil value clear, turn LED off
      digitalWrite(LED, LOW);
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}