#include <Arduino.h>

#include "pinout.h"
#include "motors.h"

int state;

void setup() {
  Serial.begin(115200);
  setupAGR();
  setupBWL();
}

int steps=400;
int sleepTime = 10000;

void loop() {
  Serial.println("Forward");
  fwdAGR();
  wakeAGR();
  stpAGR(steps);
  slpAGR();
  delay(sleepTime);

  Serial.println("Backward");
  bwdAGR();
  wakeAGR();
  stpAGR(steps);
  slpAGR();
  delay(sleepTime);
}