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



  Created on November 11, 2024

  By Zachary Schultz



*/
# 28 "D:\\Github\\HGV\\rems006-Arduino\\Primary\\Primary.ino"
// Initializing libraries
# 30 "D:\\Github\\HGV\\rems006-Arduino\\Primary\\Primary.ino" 2
# 31 "D:\\Github\\HGV\\rems006-Arduino\\Primary\\Primary.ino" 2
# 32 "D:\\Github\\HGV\\rems006-Arduino\\Primary\\Primary.ino" 2
# 33 "D:\\Github\\HGV\\rems006-Arduino\\Primary\\Primary.ino" 2
// #include <ModbusRTUServer.h>
// #include <ModbusServer.h>
// #include <ModbusTCPServer.h>

// Initializing pins





SoftwareSerial RS485Serial(SoftRO, SoftDI); // RX TX

void setup()
{
}

void loop()
{
}
