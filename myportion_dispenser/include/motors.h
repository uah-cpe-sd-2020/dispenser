#ifndef MOTORS_H
#define MOTORS_H

#include "pinout.h"
#include "auger.h"
#include "bowl.h"

void setupSTPRs() {
    pinMode(STPR_SLP_RST, OUTPUT);
    pinMode(STPR_DIR, OUTPUT);

    digitalWrite(STPR_SLP_RST, LOW);
    digitalWrite(STPR_DIR, HIGH);

    setupAGR();
    setupBWL();
}

void slpSTPRs() {
    digitalWrite(STPR_SLP_RST, LOW);
}

void wakeSTPRs() {
    digitalWrite(STPR_SLP_RST, HIGH);
}

void fwdSTPRs() {
    digitalWrite(STPR_DIR, LOW);
}

void bwdSTPRs() {
    digitalWrite(STPR_DIR, HIGH);
}

void testSTPRs() {
    wakeSTPRs();

    fwdSTPRs();

    stpBWL(200);
    stpAGR(200);

    bwdSTPRs();

    stpBWL(200);
    stpAGR(200);
    
    delay(2000);
}

#endif