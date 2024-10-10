# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
# 2 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino" 2
# 3 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino" 2

// Pins List





// Initialize Library
SoftwareSerial modbusSerial(15 /* Phyical RX 1*/, 14 /* Phyical TX 0*/);
ModbusRTUMaster modbus(Serial, 9); // Create Modbus Object with port for RS485

uint16_t randomfloat_UINT16[2];
float *randomfloat = (float*)randomfloat_UINT16;

uint16_t randomtime_UINT16[2];
float *randomtime = (float*)randomtime_UINT16;

bool coils[1];
void setup()
{
  pinMode(2, 0x1);

  modbus.begin(9600);
  Serial.begin(9600); // For Debuging
  delay(10000);
}

void loop()
{
  uint16_t returncode = modbus.readHoldingRegisters(1, 0, randomfloat_UINT16, 1);
  Serial.print('returncode: ');
  Serial.println(returncode);
  Serial.print('Float Raw: ');
  Serial.println(randomfloat_UINT16[0]);
  Serial.println(randomfloat_UINT16[1]);
  Serial.print('Float: ');
  Serial.println(randomfloat[0]);
    delay(5000);
  Serial.println('--------------------------------')
}

}
bool debug(uint16_t message){
  uint16_t returnCode = message;
    if (returnCode == 0) {
      return true;
  }
  else {
    // Shows error Message in Debug Terminal
    Serial.print("Error Code: ");
    Serial.println(returnCode);
    return false;
  }
}
