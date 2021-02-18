#include <Arduino.h>
// #include <SPI.h>

#include "serial.h"
#include "pinout.h"
#include "motors.h"
#include "pes.h"

int state;

void setup() {
  setupSerialMonitoring();
  setupAGR();
  // setupBWL();
  setupPES();
}

void loop() {
  Serial.println("We're printing");
  delay(1000);
}