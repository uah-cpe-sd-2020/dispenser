#ifndef PES_H
#define PES_H

#include "pinout.h"

void ICACHE_RAM_ATTR pesISR();
bool PESpending = false;

void setupPES() {
    pinMode(PES, INPUT);
    attachInterrupt(digitalPinToInterrupt(PES), pesISR, FALLING);
}

int getPESVal() {
    return digitalRead(PES);
}

/// Interrupt Handler for the PES
/// Only accepts once interrupt every 200ms as debounce
/// Does nothing if interrupt already pending
void pesISR() {
    if(PESpending) return;

    static uint64_t last_interrupt_time = 0;
    uint64_t current_interrupt_time = millis();
    
    if (current_interrupt_time - last_interrupt_time > 200)
    {
        PESpending = true;
    }
    last_interrupt_time = current_interrupt_time;
}

#endif