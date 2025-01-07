#include <ArduinoJson.h>
#include "conf.h"

JsonDocument doc;
String SensorJson;

String PrimaryJson(bool Smoke)
{ // add more stuff later
    doc["Primary"] = PrimaryNum;
    doc["Smoke"] = Smoke;

    serializeJson(doc, SensorJson);
    doc.clear();
    Serial.println(SensorJson);
    return SensorJson;
}

String SecondaryJson(int SecondaryNum, bool DiscreteInputs[NumSecondary], float FloatRegisters[NumSecondary])
{
    doc["Primary"] = PrimaryNum;
    doc["Secondary"] = SecondaryNum;

    for (int a = 0; a < IRAddress / 2; a++)
    {
        doc["FR"][a] = FloatRegisters[a];
        doc["DI"][a] = DiscreteInputs[a];
    }

    serializeJson(doc, SensorJson);
    doc.clear();
    Serial.println(SensorJson);
    return SensorJson;
}