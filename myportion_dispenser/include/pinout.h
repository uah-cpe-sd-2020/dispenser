#ifndef PINOUT_H
#define PINOUT_H

/// Steppers have SLP and RST tied together
#define STPR_SLP_RST D3
#define STPR_DIR D0

/// Stepper Driver Auger
#define STPR_AGR_STP D2

/// Stepper Driver Bowl
#define STPR_BWL_STP D4

/// Photo Electric Switch (PES)
#define PES D1

/// RC522 RFID Reader
#define RFID_CS 11
#define RFID_SCK 06
#define RFID_MOSI 08
#define RFID_MISO 07
#define RFID_IRQ 09
#define RFID_RST 10

/// Angular position sensor
#define POS A0

#endif