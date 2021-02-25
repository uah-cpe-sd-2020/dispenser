#ifndef AUGER_H
#define AUGER_H

#include <Arduino.h>

void setupAGR() {
    pinMode(STPR_AGR_STP, OUTPUT);
    digitalWrite(STPR_AGR_STP, LOW);
}

void stpAGR(int numSteps) {
    int timeVal = 5;
    for (int i = 0; i < numSteps; i++)
    {
        digitalWrite(STPR_AGR_STP, LOW);
        delay(timeVal);
        digitalWrite(STPR_AGR_STP, HIGH);
        delay(timeVal);
    }
}

#endif