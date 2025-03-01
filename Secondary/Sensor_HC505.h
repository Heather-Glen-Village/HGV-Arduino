#include "conf.h"

// Setting pinMode to Read
void initializeHC505()
{
    pinMode(HC505_PIN, INPUT);
}

// Reading Pin
bool DetectMotion()
{
    return digitalRead(HC505_PIN);
}