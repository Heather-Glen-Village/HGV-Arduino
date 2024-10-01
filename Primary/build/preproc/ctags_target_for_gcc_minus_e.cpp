# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
//#define DI 0
//#define RO 1



int DERE_POWER = 0; // Start Receiving
int Count = 0;

void setup() {
    pinMode(2, 0x1);
    pinMode(8, 0x1);
    Serial.begin(9600);

    digitalWrite(8, DERE_POWER);
    digitalWrite(2, DERE_POWER);
}

void loop(){
    digitalWrite(8, DERE_POWER);
    digitalWrite(2, DERE_POWER);
    delay(1000);
    if (DERE_POWER == 1){
        Serial.println(Count);
        Serial.flush();
        DERE_POWER = 0;
    }
    else if(Serial.available() != 0){
        Count = Serial.parseInt();
        Serial.print("Got: ");
        Serial.println(Count);
        Serial.print("Sending: ");
        Count++;
        DERE_POWER = 1;
    }
}
