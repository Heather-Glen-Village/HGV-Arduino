# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
//#define DI 0
//#define RO 1



int DERE_POWER = 0; // Start Recieving
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

    if(Serial.available() > 0){ // Receiver Code
        Count = Serial.parseInt();
        DERE_POWER = 1;
        delay(1000);
    }
    else if (DERE_POWER == 1){ // Sender Code
        Serial.println(Count++); // send a message 
        Serial.flush(); // wait till other board get the message
        DERE_POWER = 0;
    }
}
