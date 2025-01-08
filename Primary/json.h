#include <ArduinoJson.h>
#include "conf.h"

JsonDocument doc;
String SensorJson;

String PrimaryJson(bool Smoke)
{ 
// Creates Json with Information that they Primary has 
// add more stuff later
    doc["Primary"] = PrimaryNum;
    doc["Smoke"] = Smoke;

    serializeJson(doc, SensorJson); // Turn Json into something that can be send via Serial
    doc.clear(); // clears memeory so that this info doesn't show when creating another Json
    Serial.println(SensorJson); // Debug
    return SensorJson;
}

String SecondaryJson(int SecondaryNum, bool DiscreteInputs[NumSecondary], float FloatRegisters[NumSecondary])
{
// Creates Json with Information that a Secondary has 
    doc["Primary"] = PrimaryNum;
    doc["Secondary"] = SecondaryNum;

    for (int a = 0; a < IRAddress / 2; a++)
    {
        doc["FR"][a] = FloatRegisters[a];
        doc["DI"][a] = DiscreteInputs[a];
    }

    serializeJson(doc, SensorJson); // Turn Json into something that can be send via Serial
    doc.clear(); // clears memeory so that this info doesn't show when creating another Json
    Serial.println(SensorJson); // Debug
    return SensorJson;
}