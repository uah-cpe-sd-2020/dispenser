#ifndef BOWL_H
#define BOWL_H

#include <Arduino.h>

void setupBWL() {
    pinMode(STPR_BWL_STP, OUTPUT);
    digitalWrite(STPR_BWL_STP, LOW);
}

void stpBWL(int numSteps) {
    int timeVal = 5;
    for (int i = 0; i < numSteps; i++)
    {
        digitalWrite(STPR_BWL_STP, LOW);
        delay(timeVal);
        digitalWrite(STPR_BWL_STP, HIGH);
        delay(timeVal);
    }
}

#endif