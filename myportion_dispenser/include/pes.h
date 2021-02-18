#ifndef PES_H
#define PES_H

#include "pinout.h"

void setupPES() {
    pinMode(PES, INPUT);
}

int getPESVal() {
    return digitalRead(PES);
}

#endif