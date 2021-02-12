#include <Arduino.h>

#include "pinout.h"
#include "motors.h"
#include "pes.h"

int state;

void setup() {
  Serial.begin(115200);
  setupAGR();
  setupBWL();
  setupPES();
}

int steps=400;
int sleepTime = 1000;

void loop() {
  int pesVal = getPESVal();
  if(pesVal) {
    Serial.println("Forward");
    fwdAGR();
    wakeAGR();
    stpAGR(steps);
    slpAGR();
    delay(sleepTime);
  } else {
  Serial.println("Backward");
    bwdAGR();
    wakeAGR();
    stpAGR(steps);
    slpAGR();
    delay(sleepTime);
  }
}