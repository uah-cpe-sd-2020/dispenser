# Hardware Choices

## Overview

We need the following

1. Stepper Motor for bowl
2. Position Sensor for Bowl
3. Stepper Motor for Auger
4. NFC Sensor for Animal Tags
5. Infrared Sensor for Bowl Overfill Detection

## Main Board

NodeMCU

- [X] Wifi
- [X] 14 GPIO pins
- [X] 1 ADC

We plan on using ArduinoIDE to program the NodeMCU. See documentation [here](https://create.arduino.cc/projecthub/najad/using-arduino-ide-to-program-nodemcu-33e899)

## Pinnout

<img src="img/nodeMCU_pinout.jpg"/>

### Left Pins

| Pin       | Connected To | Purpose |
| ---       | ------------ | ------- |
| ADC.0     | Bourn 3382 | Sense position of the bowl |
| RESERVED  |  |  |
| RESERVED  |  |  |
| GPIO.10   | RC522.2 | RFID RST |
| GPIO.09   | RC522.4 | Interrupt that RFID Arrived |
| MOSI      | RC522.6 | RFID MOSI |
| CS        | RC522.8 | RFID Chip Select |
| MISO      | RC522.5 | RFID MISO |
| SCLK      | RC522.7 | RFID Serial Clock |
| GND       |  |  |
| 3.3V      |  |  |
| EN        |  |  |
| RST       |  |  |
| GND       |  |  |
| Vin       | V++ In | Bus Bar with  |

### Right Pins

| Pin       | Connected To | Purpose |
| ---       | ------------ | ------- |
| GPIO.16   |  |  |
| GPIO.05   | PES.Out | Photo Electric Switch |
| GPIO.04   |  |  |
| GPIO.00   | A4988.B.05 | Auger Driver RST |
| GPIO.02   | A4988.B.06 | Auger Driver SLP |
| 3.3V      |  |  |
| GND       |  |  |
| GPIO.14   | A4988.B.07 | Auger Driver STEP |
| GPIO.12   | A4988.B.08 | Auger Driver DIR |
| GPIO.13   | A4988.A.05 | Bowl Driver RST |
| GPIO.15   | A4988.A.06 | Bowl Driver SLP |
| GPIO.03   | A4988.A.07 | Bowl Driver STEP |
| GPIO.01   | A4988.A.08 | Bowl Driver DIR |
| GND       |  |  |
| 3.3V      |  |  |

## Stepper Motors & Drivers

### Motor Nema 17

We will need 2x Nema 17 stepper motors.

**We need to spend some quality time and pick the one we need...**

## Driver A4988

We will need 2x A4988 Stepper Motor Drivers.

Takes 2 pins from the NodeMCU as inputs to the driver.
Sends 4 signals to the stepper motor

<img src="img/Wiring-Nema-17-Stepper-Motor-to-A4988-driver-Arduino.png"/>

This setup is documented [here](https://lastminuteengineers.com/a4988-stepper-motor-driver-arduino-tutorial/)
Additional information may be found [here](https://www.instructables.com/Stepper-Motor-With-Arduino-and-Driver-A4988/)

The drivers can be found for purchase [here](https://www.amazon.com/HiLetgo-Stepstick-Stepper-Printer-Compatible/dp/B07BND65C8/ref=sr_1_1_sspa?crid=2VQ947H678D2K&dchild=1&keywords=a4988+stepper+motor+driver&qid=1611869357&sprefix=a4988%2Caps%2C162&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUFWVDJITEM4S0swTTgmZW5jcnlwdGVkSWQ9QTA2MDE4NzUyUzRXVVdCVFg4TFgwJmVuY3J5cHRlZEFkSWQ9QTAyNzIwMjExUExSNkNWSVJJSUI0JndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==)

<img src="img/A4988-Stepper-Motor-Driver-Pinout.png">

### Bowl Driver Pinout - A4988.A

| Pin       | Connected to | Purpose |
| ---       | ------------ | ------- |
| 01 EN     | GND |  |
| 02 MS1    | Vcc | Sets to Half Step Resolution |
| 03 MS2    | GND | Sets to Half Step Resolution |
| 04 MS2    | GND | Sets to Half Step Resolution |
| 05 RST    | NodeMCU.GPIO.13 |  |
| 06 SLP    | NodeMCU.GPIO.15 |  |
| 07 STEP   | NodeMCU.GPIO.03 |  |
| 08 DIR    | NodeMCU.GPIO.01 |  |
| 09 GND    |  |  |
| 10 VDD    | 3 or 5V |  |
| 11 1B     | Stepper |  |
| 12 1A     | Stepper |  |
| 13 2A     | Stepper |  |
| 14 2B     | Stepper |  |
| 15 GND    |  |  |
| 16 VMOT   | Power IN | Between 8V and 35V |

*Note: If we want more or less resolution, we will adjust the step size with pins 02-04*

### Auger Driver Pinout - A4988.B

| Pin       | Connected to | Purpose |
| ---       | ------------ | ------- |
| 01 EN     | GND |  |
| 02 MS1    | Vcc | Sets to Half Step Resolution |
| 03 MS2    | GND | Sets to Half Step Resolution |
| 04 MS2    | GND | Sets to Half Step Resolution |
| 05 RST    | NodeMCU.GPIO.00 |  |
| 06 SLP    | NodeMCU.GPIO.02 |  |
| 07 STEP   | NodeMCU.GPIO.14 |  |
| 08 DIR    | NodeMCU.GPIO.12 |  |
| 09 GND    |  |  |
| 10 VDD    | 3 or 5V |  |
| 11 1B     | Stepper |  |
| 12 1A     | Stepper |  |
| 13 2A     | Stepper |  |
| 14 2B     | Stepper |  |
| 15 GND    |  |  |
| 16 VMOT   | Power IN | Between 8V and 35V |

*Note: If we want more or less resolution, we will adjust the step size with pins 02-04*

## Bowl Position - Bourn 3382

We plan on using a Bourn 3382 angular position sensor.  This will be tied to the ADC pin on the NodeMCU.

<img src="img/bourn-3382.jpeg"/>

[Spec Sheet](https://www.bourns.com/pdfs/3382.pdf)

## Bowl Overfill Detection - PhotoElectric Switch

We are using an PhotoElectric Switch to determine whether the bowl is full or not.

<img src="img/photoelectricswitch-pinout.jpg"/>

We plan on buying [this one](https://www.amazon.com/Infrared-Avoidance-Transmitting-Receiving-Photoelectric/dp/B07PFCC76N/ref=sr_1_1_sspa?dchild=1&keywords=ir+sensor&qid=1611867120&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExSEVUOVhPWDRGM0VPJmVuY3J5cHRlZElkPUEwMTE1NTYzMjIxMUFQUVFRUFFGUiZlbmNyeXB0ZWRBZElkPUExMDEyMzcyMU9aR0JHOUFHSk1GUSZ3aWRnZXROYW1lPXNwX2F0ZiZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=)

### PhotoElectric Switch Pinout

Known as PES

| Pin   | Connected to | Purpose |
| ---   | ------------ | ------- |
| Out | NodeMCU.GPIO.05 |  |
| GND |  |  |
| Vcc | Vcc | 3.3V or 5V (Check Spec sheet on delivery) |

## NFC Scanning - RC522

We plan to use an RC522 RFID reader.

<img src="img/RC522-RFID-Reader-Writer-Module-Pinout.png"/>

More documentation can be found [Here](https://lastminuteengineers.com/how-rfid-works-rc522-arduino-tutorial/)

### RC522 Pinout

| Pin   | Connected to | Purpose |
| ---   | ------------ | ------- |
| 8     | NodeMCU.CS | Chip Select |
| 7     | NodeMCU.SCK | Serial Clock |
| 6     | NodeMCU.MOSI |  |
| 5     | NodeMCU.MISO |  |
| 4     | NodeMCU.GPIO.09 | IRQ alerts micro-controller of RFID present |
| 3     | GND |  |
| 2     | NodeMCU.GPIO.10 | RST.  Board resets when low input is received |
| 1     | Vcc | Needs 3.3V __(NO 5 V)__|
