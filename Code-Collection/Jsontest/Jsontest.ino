#include <ArduinoJson.h>

#define PrimaryNum 1 //Uused to Idenity Primary Might want to use Room Number Later
#define NumSecondary 4 // Amount of Secondary Boards Being Used

#define DIAddress 5 // Number of used Discrete Inputs Address
#define IRAddress 8 // Number of used Input Register Addresss

bool discreteInputs[NumSecondary][DIAddress]={
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {1, 0, 0, 0}
};
float FloatRegisters[NumSecondary][IRAddress/2]={
    {12.45, 13.43, 11.43, 11.43},
    {43.5, 43.5, 43.5, 43.5},
    {56.7, 56.7, 56.7, 56.7},
    {78.9, 78.9, 78.9, 78.9}
};

  void setup() {
    Serial.begin(9600);
    while (!Serial) {
        delay(1);
    }
  StaticJsonDocument<256> doc; // We going to need a bigger Json
  char SensorJson[300]; // should be like 10%  bigger then the JSON I Think

  // Populate the JSON document
  for (int s = 0; s < NumSecondary; s++)
  {
    doc["Primary"] = PrimaryNum;
    doc["Secondary"] = s+1;

    // Add data to the Float FloatRegisters array
    JsonArray FR = doc.createNestedArray("FR");
    FR.add(FloatRegisters[s][0]);
    FR.add(FloatRegisters[s][1]);
    FR.add(FloatRegisters[s][2]);
    FR.add(FloatRegisters[s][3]);

    // Add data to the "DI" array
    JsonArray DI = doc.createNestedArray("DI");
    DI.add(discreteInputs[s][0]);
    DI.add(discreteInputs[s][1]);
    DI.add(discreteInputs[s][2]);
    DI.add(discreteInputs[s][3]);

    // Serialize JSON to a string and print it
    serializeJson(doc, SensorJson);
    Serial.println(SensorJson);
    doc.clear();
    delay(5000);
  }
}

void loop() {
}