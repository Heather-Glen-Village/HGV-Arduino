# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
# 2 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino" 2



//#define DI 0
//#define RO 1




SoftwareSerial RS485Serial(17 /* A3*/, 16 /* A2*/); // RX TX

void setup()
{
  pinMode(2, 0x1);
  pinMode(8, 0x1);
  Serial.begin(9600);
  RS485Serial.begin(19200);
  digitalWrite(8, 0x0);
}

void loop() {
  digitalWrite(8, 0x0);

  int Serial_A = Serial.available();
  int Soft_A = RS485Serial.available();

  if (Serial_A > 0) {
    Serial.println(Serial_A);
    char IncomingMessage = Serial.read();

    Serial.print("Received: ");
    Serial.println(IncomingMessage);

    bool led_power = !digitalRead(2);
    Serial.println(led_power);
    digitalWrite(2, led_power);

  }
  else if (Soft_A > 0) {
    Serial.println(Soft_A);
    bool IncomingMessage = RS485Serial.read();
    Serial.print("Received: ");
    Serial.println(IncomingMessage);
    if (IncomingMessage == 1) {
      digitalWrite(2, !digitalRead(2));
    }
    else {
      Serial.println("Unknown message");
    }
  }

}
