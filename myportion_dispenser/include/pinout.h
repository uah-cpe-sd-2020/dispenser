#ifndef PINOUT_H
#define PINOUT_H

/// Stepper Driver Auger
#define STPR_AGR_RST 00
#define STPR_AGR_SLP 02
#define STPR_AGR_STP 14
#define STPR_AGR_DIR 12

/// Stepper Driver Bowl
#define STPR_BWL_RST 13
#define STPR_BWL_SLP 15
#define STPR_BWL_STP 03
#define STPR_BWL_DIR 01

/// Photo Electric Switch (PES)
#define PES 05

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