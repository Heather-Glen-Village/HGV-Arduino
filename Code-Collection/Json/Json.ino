#include <ArduinoJson.h>

bool discreteInputs[2][3] = {
    {1, 0, 1},
    {0, 0, 1}};

float FloatRegisters[2][3] = {
    {12.5, 13.5, 69},
    {13.5, 23.5, 12}};

bool smoke = 1;
void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop()
{
    // put your main code here, to run repeatedly:
    sendData(discreteInputs, FloatRegisters, smoke);
    delay(5000);
}

void sendData(bool discreteInputs[2][3], float FloatRegisters[2][6 / 2], bool Smoke)
{
    // turn data into a Json and Send it to NodeRed

    StaticJsonDocument<512> doc; // We going to need a bigger Json
    char SensorJson[512];        // should be like 10%  bigger then the JSON I Think

    Serial.println("Sending Data to NodeRed");
    // Create Json for Every Secondary
    for (int s = 0; s < 2; s++)
    {
        doc["Primary"] = 1;
        doc["Secondary"] = s + 1;

        // Float Register
        JsonArray FR = doc.createNestedArray("FR");
        for (int a = 0; a < 6 / 2; a++)
        {
            FR.add(FloatRegisters[s][a]);
        }

        // Discrete Inputs
        JsonArray DI = doc.createNestedArray("DI");
        for (int a = 0; a < 3; a++)
        {
            DI.add(discreteInputs[s][a]);
        }

        // Serialize JSON to a string and print it
        Serial.println();
        serializeJson(doc, SensorJson);
        Serial.println(SensorJson);
        // client.publish(SensorTopic, SensorJson);
        doc.clear();
    }
    // Json for the Primary
    doc["Primary"] = 1;
    doc["Smoke"] = Smoke;

    Serial.println();
    serializeJson(doc, SensorJson);
    Serial.println(SensorJson);
    // client.publish(SensorTopic, SensorJson);
    doc.clear();
}