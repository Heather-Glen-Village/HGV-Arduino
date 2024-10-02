#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(10, 0, 0, 177);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Ethernet.begin(mac, ip);

  Serial.print("The gateway IP address is: ");
  Serial.println(Ethernet.gatewayIP());
}

void loop () {}