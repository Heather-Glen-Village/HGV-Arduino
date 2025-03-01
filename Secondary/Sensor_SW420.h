#include "conf.h"

// Setting pinMode to Read
void initializeSW420()
{
    pinMode(SW420_PIN, INPUT);
}

// Reading Pin
bool DetectVibration()
{
    return digitalRead(HC505_PIN);
}