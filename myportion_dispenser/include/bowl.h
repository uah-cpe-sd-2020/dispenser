#ifndef BOWL_H
#define BOWL_H

#include <Arduino.h>

#include "pinout.h"

void setupBWL() {
    pinMode(STPR_BWL_RST, OUTPUT);
    pinMode(STPR_BWL_SLP, OUTPUT);
    pinMode(STPR_BWL_STP, OUTPUT);
    pinMode(STPR_BWL_DIR, OUTPUT);

    digitalWrite(STPR_BWL_RST, LOW);
    digitalWrite(STPR_BWL_SLP, LOW);
    digitalWrite(STPR_BWL_STP, LOW);
    digitalWrite(STPR_BWL_DIR, LOW);
}


void slpBWL() {
    digitalWrite(STPR_BWL_RST, LOW);
    digitalWrite(STPR_BWL_SLP, LOW);
}

void wakeBWL() {
    digitalWrite(STPR_BWL_RST, HIGH);
    digitalWrite(STPR_BWL_SLP, HIGH);
}

void fwdBWL() {
    digitalWrite(STPR_BWL_DIR, LOW);
}

void bwdBWL() {
    digitalWrite(STPR_BWL_DIR, HIGH);
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

void testBWL() {
    wakeBWL();
    fwdBWL();
    bwdBWL();
    slpBWL();
}

#endif