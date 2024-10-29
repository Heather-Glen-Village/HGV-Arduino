# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino"
# 2 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino" 2
# 3 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Secondary-1\\Secondary-1.ino" 2
const int MOTION_SENSOR_PIN = 5;







ModbusRTUSlave modbus(Serial, 9);

bool coils[1];
uint16_t InputRegisters[6];
float *FloatRegisters = (float*)InputRegisters;

int motionCurrentState = 0x0;
int motionPreviousState = 0x0;

// Initialize DHT sensor
DHT dht(3 /* Pin D3*/, DHT22 /* DHT 22 (AM2302)*/);

void setup() {

  modbus.configureCoils(coils, 1);
  modbus.configureInputRegisters(InputRegisters, 2);
  modbus.begin(1,9600);
  Serial.begin(9600); // Start serial communication
  dht.begin(); // Initialize the DHT sensor
  pinMode(MOTION_SENSOR_PIN, 0x0); // Sensor is input
  pinMode(2, 0x1);
}

void loop() {
  if(Serial.available() !=0){
  modbus.poll();
  }

  motionPreviousState = motionCurrentState;
  motionCurrentState = digitalRead(MOTION_SENSOR_PIN);
 if((motionCurrentState != -1)&&(motionPreviousState!= -1)){
  //Serial.println("lkjbeghjtg");    // Yup it works
 }
  if (motionPreviousState == 0x0 && motionCurrentState==0x1){
  Serial.println("MOTION DETECTED!!");
  coils[0] = true;
  }

  if(motionPreviousState==0x1 && motionCurrentState==0x0){
  Serial.println("MOTION STOPPED.");
   coils[0] = false;
  }
  else {
    coils[0] = false;
  }

  // Read temperature as Celsius
  float temperature = dht.readTemperature();
  // Read humidity
  float humidity = dht.readHumidity();

  FloatRegisters[0] = temperature;
  FloatRegisters[1] = humidity;

  // Check if any reads failed and exit early
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

Serial.println("Sensor readings: ");
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print(", Humidity: ");
  Serial.println(humidity);
   delay(2000); // Wait a few seconds between readings

}
