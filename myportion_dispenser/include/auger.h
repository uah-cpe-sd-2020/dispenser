#ifndef AUGER_H
#define AUGER_H

#include <Arduino.h>

#include "pinout.h"

void setupAGR() {
    pinMode(STPR_AGR_RST, OUTPUT);
    pinMode(STPR_AGR_SLP, OUTPUT);
    pinMode(STPR_AGR_STP, OUTPUT);
    pinMode(STPR_AGR_DIR, OUTPUT);

    digitalWrite(STPR_AGR_RST, LOW);
    digitalWrite(STPR_AGR_SLP, LOW);
    digitalWrite(STPR_AGR_STP, LOW);
    digitalWrite(STPR_AGR_DIR, LOW);
}


void slpAGR() {
    digitalWrite(STPR_AGR_RST, LOW);
    digitalWrite(STPR_AGR_SLP, LOW);
}

void wakeAGR() {
    digitalWrite(STPR_AGR_RST, HIGH);
    digitalWrite(STPR_AGR_SLP, HIGH);
}

void fwdAGR() {
    digitalWrite(STPR_AGR_DIR, LOW);
}

void bwdAGR() {
    digitalWrite(STPR_AGR_DIR, HIGH);
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

void testAGR() {
    wakeAGR();
    fwdAGR();
    bwdAGR();
    slpAGR();
}

#endif