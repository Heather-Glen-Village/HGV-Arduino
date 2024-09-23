#define LED 2
#define SLAVE_EN 1 // Change this to RS485 Pin
  
void setup(){
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}
  
void loop(){
    while(Serial.available()) // if there is something to read in the serial
    {
        Serial.println(Serial.read());
        if(Serial.read() == 'A')
        {
            //digitalWrite(LED, !digitalRead(LED));
            Serial.println("Message received");
        }
    }
}