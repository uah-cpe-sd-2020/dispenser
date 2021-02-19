#include <Arduino.h>
// #include <SPI.h>

#include "serial.h"
#include "pinout.h"
#include "motors.h"
#include "pes.h"

int state;

void setup() {
  setupSerialMonitoring();
  setupPES();
  setupSTPRs();
}

void loop() {
  if(PESpending) {
    Serial.println("Testing Steppers");
    testSTPRs();
    PESpending = false;
  }
}