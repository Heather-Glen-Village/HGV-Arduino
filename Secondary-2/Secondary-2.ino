#define LED 2
#define DI 0
#define RO 1
#define SLAVE_EN 8

void setup(){
    digitalWrite(LED, OUTPUT);
    digitalWrite(SLAVE_EN, OUTPUT);
    Serial.begin(9600);
    digitalWrite(SLAVE_EN, LOW);
}

void loop(){
    while(Serial.available())
    {
        char Message = Serial.read(); 
        Serial.println(Message);
        if(Message == 'A')
        {
            digitalWrite(LED, !digitalRead(LED));
        }
    }
}