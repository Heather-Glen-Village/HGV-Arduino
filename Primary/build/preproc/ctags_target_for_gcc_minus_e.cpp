# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
# 2 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino" 2
# 3 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino" 2

// Pins List





// Initialize Library
SoftwareSerial modbusSerial(15 /* Phyical RX 1*/, 14 /* Phyical TX 0*/);
ModbusRTUMaster modbus(Serial, 9); // Create Modbus Object with port for RS485

bool SlaveLED = 1; // Enable Slave LED by default

uint16_t randomfloat_UINT16[];
float *randomfloat = (float*)randomfloat_UINT16;

uint16_t randomtime_UINT16[];
float *randomtime = (float*)randomtime_UINT16;

void setup()
{
  pinMode(2, 0x1);

  modbus.begin(9600);
  Serial.begin(9600); // For Debuging
}

void loop()
{
  if (modbus)

  if (returncode == 0)
  {
    if (SlaveLED == 1)
    {
      SlaveLED = 0;
      Serial.println("SlaveLED Enabled");
    }
    else
    {
      SlaveLED = 1;
      Serial.println("SlaveLED Disabled");
    }
  }
  else
  {
    // Shows error Message in Debug Terminal
    Serial.print("S1 Code: ");
    Serial.println(returncode);
  }
  delay(2000);
}
