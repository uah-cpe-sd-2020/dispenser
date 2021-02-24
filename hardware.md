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

[NodeMCU](https://www.nodemcu.com/index_en.html)

The NodeMCU can be purchased [here](https://www.amazon.com/gp/product/B081CSJV2V/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)

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
| MOSI      |  |  |
| CS        |  |  |
| MISO      |  |  |
| SCLK      |  |  |
| GND       |  |  |
| 3.3V      |  |  |
| EN        |  |  |
| RST       |  |  |
| GND       |  |  |
| Vin       | V++ In | Bus Bar with  |

### Right Pins

| Pin       | Connected To | Purpose |
| ---       | ------------ | ------- |
| GPIO.16   | A4988.B.08 / A4988.A.08 | Bowl Driver DIR / Auger Driver DIR |
| GPIO.05   | PES.Out | Photo Electric Switch |
| GPIO.04   | A4988.B.07 | Auger Driver STEP |
| GPIO.00   | A4988.B.05 / A4988.B.06 / A4988.A.05 / A4988.A.06 | Auger Driver RST / Auger Driver SLP / Bowl Driver SLP / Bowl Driver RST |
| GPIO.02   | A4988.A.07 | Bowl Driver STEP |
| 3.3V      |  |  |
| GND       |  |  |
| GPIO.14   | RC522.7 | RFID Serial Clock |
| GPIO.12   | RC522.5 | RFID MISO |
| GPIO.13   | RC522.6 | RFID MOSI |
| GPIO.15   | RC522.8 | RFID Chip Select |
| GPIO.03   |  |  |
| GPIO.01   |  |  |
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
| 05 RST    | NodeMCU.GPIO.00 |  |
| 06 SLP    | NodeMCU.GPIO.00 |  |
| 07 STEP   | NodeMCU.GPIO.02 |  |
| 08 DIR    | NodeMCU.GPIO.16 |  |
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
| 06 SLP    | NodeMCU.GPIO.00 |  |
| 07 STEP   | NodeMCU.GPIO.04 |  |
| 08 DIR    | NodeMCU.GPIO.16 |  |
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

The Bourn 3382 can be purchased [here](https://www.digikey.com/en/products/detail/3382G-1-503G/3382G-1-503GCT-ND/2080240?utm_medium=email&utm_source=oce&utm_campaign=3480_OCE21RT&utm_content=productdetail_US&utm_cid=1679481&so=67808724&mkt_tok=eyJpIjoiWkRVelpqZ3hZVEl4T1RZeSIsInQiOiJuMXNcLzJmdG14Vk5VdjhwejlMdm9QcEg2XC9IZXJDZnIxemVzcUxIYk9VNHRrZW82dlcrUzNNWnVFY3g3Tjk3cTgwYkFtakZiRmo3VmRlQWQzWEZPZTNXaG1VcTliMG5mSG9YRjY4Z1FvUU5JWkNsbmJnZm9YZkpCUmNaOXRXNEVGIn0%3D)

## Bowl Overfill Detection - PhotoElectric Switch

We are using an PhotoElectric Switch to determine whether the bowl is full or not.

<img src="img/photoelectricswitch-pinout.jpg"/>

The PhotoElectric Switch can be purchased [here](https://www.amazon.com/Infrared-Avoidance-Transmitting-Receiving-Photoelectric/dp/B07PFCC76N/ref=sr_1_1_sspa?dchild=1&keywords=ir+sensor&qid=1611867120&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExSEVUOVhPWDRGM0VPJmVuY3J5cHRlZElkPUEwMTE1NTYzMjIxMUFQUVFRUFFGUiZlbmNyeXB0ZWRBZElkPUExMDEyMzcyMU9aR0JHOUFHSk1GUSZ3aWRnZXROYW1lPXNwX2F0ZiZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=)

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

The RC522 RFID Reader can be purchased [here](https://www.amazon.com/gp/product/B07KGBJ9VG/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)

### RC522 Pinout

| Pin   | Connected to | Purpose |
| ---   | ------------ | ------- |
| 8     | NodeMCU.GPIO.15 | Chip Select |
| 7     | NodeMCU.GPIO.14 | Serial Clock |
| 6     | NodeMCU.GPIO.13 |  |
| 5     | NodeMCU.GPIO.12 |  |
| 4     | NodeMCU.GPIO.09 | IRQ alerts micro-controller of RFID present |
| 3     | GND |  |
| 2     | NodeMCU.GPIO.10 | RST.  Board resets when low input is received |
| 1     | Vcc | Needs 3.3V __(NO 5 V)__|
