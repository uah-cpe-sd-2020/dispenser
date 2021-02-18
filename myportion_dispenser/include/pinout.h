#ifndef PINOUT_H
#define PINOUT_H

/// Stepper Driver Auger
#define STPR_AGR_RST 05
#define STPR_AGR_SLP 04
#define STPR_AGR_STP 00
#define STPR_AGR_DIR 02

/// Stepper Driver Bowl
#define STPR_BWL_RST 14
#define STPR_BWL_SLP 12
#define STPR_BWL_STP 13
#define STPR_BWL_DIR 15

/// Photo Electric Switch (PES)
#define PES 16

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