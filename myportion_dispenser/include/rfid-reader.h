#ifndef RFID_READER_H
#define RFID_READER_H

#include <SPI.h>
#include <MFRC522.h>
#include "pinout.h"


MFRC522 mfrc522(RFID_CS, RFID_RST);
MFRC522::MIFARE_Key key;

volatile bool bNewInt = false;
byte regVal = 0x7F;
void activateRec(MFRC522 mfrc522);
void clearInt(MFRC522 mfrc522);

void ICACHE_RAM_ATTR readCard();

void setupRFID(void) {
    SPI.pins(RFID_SCK, RFID_MISO, RFID_MOSI, RFID_CS);
    SPI.begin();
    mfrc522.PCD_Init();

    /* setup the IRQ pin*/
    pinMode(RFID_IRQ, INPUT_PULLUP);
    /*
    * Allow the ... irq to be propagated to the IRQ pin
    * For test purposes propagate the IdleIrq and loAlert
    */
    regVal = 0xA0; //rx irq
    mfrc522.PCD_WriteRegister(mfrc522.ComIEnReg, regVal);

    bNewInt = false; //interrupt flag
    /*Activate the interrupt*/
    attachInterrupt(digitalPinToInterrupt(RFID_IRQ), readCard, FALLING);
    
    bNewInt = false;
}

/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
/**
 * MFRC522 interrupt serving routine
 */
void readCard(void) {
  bNewInt = true;
}

/*
 * The function sending to the MFRC522 the needed commands to activate the reception
 */
void activateRec(MFRC522 mfrc522) {
  mfrc522.PCD_WriteRegister(mfrc522.FIFODataReg, mfrc522.PICC_CMD_REQA);
  mfrc522.PCD_WriteRegister(mfrc522.CommandReg, mfrc522.PCD_Transceive);
  mfrc522.PCD_WriteRegister(mfrc522.BitFramingReg, 0x87);
}

/*
 * The function to clear the pending interrupt bits after interrupt serving routine
 */
void clearInt(MFRC522 mfrc522) {
  mfrc522.PCD_WriteRegister(mfrc522.ComIrqReg, 0x7F);
}

void handleRFIDInterrupt(void) {
    Serial.print(F("Interrupt. "));
    mfrc522.PICC_ReadCardSerial(); //read the tag data
    // Show some details of the PICC (that is: the tag/card)
    Serial.print(F("Card UID:"));
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println();

    clearInt(mfrc522);
    mfrc522.PICC_HaltA();
    bNewInt = false;
}

#endif