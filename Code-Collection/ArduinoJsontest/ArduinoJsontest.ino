#include <ArduinoJson.h>

bool discreteInputs[2][3] = {
    {1, 0, 1},
    {0, 0, 1}};

float FloatRegisters[2][3] = {
    {12.5, 13.5, 69},
    {13.5, 23.5, 12}};

bool smoke = 1;

void sendData(bool discreteInputs[2][3], float FloatRegisters[2][6 / 2], bool Smoke)
{
    JsonDocument doc;
    char SerialJson[512];

    doc["Primary"] = 1;
    doc["Secondary"] = 2;

    doc["IR"][0] = 12.53;
    doc["IR"][1] = 13.53;
    doc["IR"][2] = 16.53;

    doc["DI"][0] = 0;
    doc["DI"][1] = 1;
    doc["DI"][2] = 0;

    serializeJson(doc, SerialJson);
    Serial.println(SerialJson);
    doc.clear();
}
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
