# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
# 2 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino" 2
//#include <NeoSWSerial.h>
# 4 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino" 2

// Pins List





SoftwareSerial modbusSerial(15 /*Phyical RX 1*/, 14 /*Phyical TX 0*/);
ModbusRTUMaster modbus(modbusSerial, 9); // Create Modbus Object with port for RS485


bool SlaveLED = 1; // Enable

void setup() {
  pinMode(2, 0x1);
  digitalWrite(2, SlaveLED);
  //modbus.setTimeout(500);
  modbus.begin(9600); // Baud Rate  | Config?
  Serial.begin(9600);
}

void loop() {
  digitalWrite(2, SlaveLED);
  modbus.writeSingleCoil(0,0,SlaveLED);
  if (SlaveLED == 1) {
      SlaveLED = 0;
      Serial.println("SlaveLED Enabled");
    }
    else {
      SlaveLED = 1;
      Serial.println("SlaveLED Disabled");
    }


  /*uint8_t returncode = modbus.writeSingleCoil(1, 0, SlaveLED);

  delay(1000);

  uint8_t returncode2 = modbus.writeSingleCoil(2, 0, SlaveLED);

  if (returncode == 0 && returncode2 == 0) {

    if (SlaveLED == 1) {

      SlaveLED = 0;

      Serial.println("SlaveLED Enabled");

    } 

    else {

      SlaveLED = 1;

      Serial.println("SlaveLED Disabled");

    }

  }

  else{

    Serial.print("S1 Code: ");

    Serial.println(returncode);

    Serial.print("S2 Code: ");

    Serial.println(returncode2);

  }*/
# 58 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
  delay(5000);
}
