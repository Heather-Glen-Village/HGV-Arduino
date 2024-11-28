#include <SPI.h>
#include <Ethernet.h>

#define LED 2


byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF 
};
EthernetClient client;

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Board Finder Started!");
  delay(1000);

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    } else if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
      Serial.println("Board is most likely not the Priamry Board");
  } else {
    Serial.println(Ethernet.localIP());
    Serial.println("This is a Priamry Board");
  }


  Serial.println("Press Enter into the Terminal to Switch LED");
  Serial.println("Enter Character To cause the LED to Flash");
  digitalWrite(LED, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);

}

void loop() {
  
  if (Serial.available() > 0)  {
    Serial.read();
    digitalWrite(LED, !digitalRead(LED));
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    if(digitalRead(LED) == HIGH) {
        Serial.println("LED is Now Enabled");
    }
    else {
        Serial.println("LED is Now Disable");
    }
  }
  delay(500);
}
