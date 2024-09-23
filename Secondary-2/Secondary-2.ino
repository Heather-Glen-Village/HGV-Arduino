#define LED 2
#define SLAVE_EN 0 // Change this to RS485 Pin
  
void setup(){
  pinMode(LED, OUTPUT);
  pinMode(SLAVE_EN, OUTPUT);
  Serial.begin(9600);
  digitalWrite(SLAVE_EN, LOW);
}
  
void loop(){
    while(Serial.available()) // if there is something to read in the serial
    {
        if(Serial.read() == 'test')
        {
            digitalWrite(LED, !digitalRead(LED));
        }
    }
}