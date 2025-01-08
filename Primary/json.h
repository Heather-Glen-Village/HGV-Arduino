#include <ArduinoJson.h>
#include "conf.h"

JsonDocument doc;
String SensorJson;

// Creates Json with Information that they Primary has 
String PrimaryJson(bool Smoke)
{ 

    doc["Primary"] = PrimaryNum;
    doc["Smoke"] = Smoke;
// add more stuff later
    serializeJson(doc, SensorJson); // Turn Json into something that can be send via Serial
    doc.clear(); // clears memeory so that this info doesn't show when creating another Json
    Serial.println(SensorJson); // Debug
    return SensorJson;
}

// Creates Json with Information that a Secondary has 
String SecondaryJson(int SecondaryNum, bool DiscreteInputs[NumSecondary], float FloatRegisters[NumSecondary])
{
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