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
    while(Serial.available() > 0)
    {
        Serial.println('N');
        if(Serial.read() == 'A')
        {
            Serial.println('E');
            digitalWrite(LED, !digitalRead(LED));
        }
    }
}