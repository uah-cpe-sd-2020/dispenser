#ifndef PINOUT_H
#define PINOUT_H

/// Steppers have SLP and RST tied together
#define STPR_SLP_RST D3 // GPIO00
#define STPR_DIR D0     // GPIO16

/// Stepper Driver Auger
#define STPR_AGR_STP D2 // GPIO04

/// Stepper Driver Bowl
#define STPR_BWL_STP D4 // GPIO02

/// Photo Electric Switch (PES)
#define PES D1          // GPIO05

/// RC522 RFID Reader
#define RFID_CS D8      // GPIO15
#define RFID_SCK D5     // GPIO14
#define RFID_MOSI D7    // GPIO13
#define RFID_MISO D6    // GPIO12
#define RFID_IRQ 9      // GPIO09
#define RFID_RST 10     // GPIO10

/// Angular position sensor
#define POS A0

#endif