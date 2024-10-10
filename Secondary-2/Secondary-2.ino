#include <DHT.h>
//#include <SPI.h>
// #include <SD.h>

#define DHTPIN 3      // Pin D3
#define DHTTYPE DHT22 // DHT 22 (AM2302)

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

const int arraySize = 5;
float temperatureArray[arraySize];

void setup() {
  Serial.begin(115200); // Start serial communication
  dht.begin();        // Initialize the DHT sensor
}

void loop() {
  delay(2000); // Wait a few seconds between readings

for(int i =0; i < arraySize; i++){
  // Move bracket down but then it says temperature was not declared in this scene?
}


  // Read temperature as Celsius
  float temperature = dht.readTemperature();
  // Read humidity
  float humidity = dht.readHumidity();

  // Check if any reads failed and exit early
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print the results to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

//File dataFile = SD.open("dht.data.txt", FILE_WRITE);

  
}