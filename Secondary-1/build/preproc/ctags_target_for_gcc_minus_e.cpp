# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
# 2 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino" 2

// Pins List

//#define TX  0
//#define RX  1



ModbusRTUSlave modbus(Serial, 9); // Create Modbus Object

bool coils[1]; // Creating an array where the Coils can go | Read & Write Only Bools

void setup() {
  pinMode(2, 0x1);

  modbus.configureCoils(coils, 1); // Says where The Coils can go and How many there are?
  //odbus.setResponseDelay(1500); //| used to make delay from the resonds
  modbus.begin(1, 9600); // ID | Baud Rate  | Config?


}

void loop() {

  modbus.poll(); // Check if there was a request

  digitalWrite(2, coils[0]);
 // delay(100);
}
