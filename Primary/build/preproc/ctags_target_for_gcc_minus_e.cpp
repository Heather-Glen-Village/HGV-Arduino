# 1 "D:\\Github\\HGV\\rems006-Arduino\\Primary\\Primary.ino"


/*

  Primary Arduino Control



  This sketch is the Code That lets the Priamry Act as a RTC Master, TCP Server, and Control All Sensor and System Connected



  Pin List

    - D2 LED

    - D3 Smoke

    - D4 Heat On

    - D5 Water Off

    - D6 Power Off

    - D7 Cool On

    - D8 Eth-Int?

    - D9 Dere Power (Unused)

    - D10 Eth-CSN

    - D11 Eth-MOSI

    - D12 Eth-MISO

    - D13 Eth-SCK

    - D16(A2) SoftRX

    - D17(A3) SoftTX



  Created on November 20, 2024

  By Zachary Schultz



*/
# 28 "D:\\Github\\HGV\\rems006-Arduino\\Primary\\Primary.ino"
// Initializing libraries
# 30 "D:\\Github\\HGV\\rems006-Arduino\\Primary\\Primary.ino" 2
# 31 "D:\\Github\\HGV\\rems006-Arduino\\Primary\\Primary.ino" 2
# 32 "D:\\Github\\HGV\\rems006-Arduino\\Primary\\Primary.ino" 2
# 33 "D:\\Github\\HGV\\rems006-Arduino\\Primary\\Primary.ino" 2
# 34 "D:\\Github\\HGV\\rems006-Arduino\\Primary\\Primary.ino" 2
// #include <ModbusRTUServer.h>
// #include <ModbusServer.h>
// #include <ModbusTCPServer.h>

// Initializing pins




// Initializing the uses of SoftwareSerial
// SoftwareSerial modbusSerial(rxPin, txPin); // RX TX

void setup()
{
  Serial.begin(9600); // for Debug
  RS485.setPins(17 /* A3*/, 16 /* A2*/, 2); // Board don't Use RE pin so set it to LED so it lights up while Sending
  if (!ModbusRTUServer.begin(1, 9600))
  {
  }
}

void loop()
{
}
