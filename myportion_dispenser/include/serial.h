#ifndef SERIAL_SETUP_H
#define SERIAL_SETUP_H

#include <Arduino.h>

void setupSerialMonitoring() {
    Serial.clearWriteError();
    Serial.flush();
    Serial.begin(115200);
    while (!Serial.availableForWrite())
    {
        // Waiting to write
    }
    Serial.println(" ");
    Serial.println("Serial Open");
}

#endif