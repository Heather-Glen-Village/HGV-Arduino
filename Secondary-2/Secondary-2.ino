#define LED 2
#define DI 0
#define RO 1

void setup(){
    digitalWrite(LED, OUTPUT);
    Serial.begin(9600);
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
    Serial.println('Not working :<');
    delay(1);
}