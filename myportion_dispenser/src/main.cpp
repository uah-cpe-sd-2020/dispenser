#include <Arduino.h>

#include "serial.h"
#include "pinout.h"
#include "motors.h"
#include "pes.h"
#include "rfid-reader.h"
#include "wifiChunks.h"

int state;

void setup() {
  setupSerialMonitoring();
  setupPES();
  setupSTPRs();
  setupRFID();
  setupWifi();
  Serial.println("End of Setup");
}

void loop() {
  if(PESpending) {
    Serial.println("Testing Steppers");
    testSTPRs();
    PESpending = false;
  }

  if (bNewInt) { //new read interrupt
    handleRFIDInterrupt();
  }

  // The receiving block needs regular retriggering (tell the tag it should transmit??)
  // (mfrc522.PCD_WriteRegister(mfrc522.FIFODataReg,mfrc522.PICC_CMD_REQA);)
  activateRec(mfrc522);

  // Check the status of the wifi connection
  checkWifiStatus();

  delay(100);
}