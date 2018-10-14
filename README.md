# RFID RDM6300 for Arduino

This will demonstrate how to use the RDM6300 to be able to read RFID tags using the Arduino software.

![RDM6300 with ESP8266](https://scontent-lht6-1.cdninstagram.com/vp/0232e097b131fcab1a0ee1e6077db93d/5C5C7C0F/t51.2885-15/e35/42756112_188748952021254_4986979122585534464_n.jpg)

## RDM630 vs RDM6300

The RDM630 and the RDM6300 are two different types of RFID readers, but are easily confused.

They share:

- Similar names
- Technical functionality
- Pin layout
- Transfer protocol
- Support 125kHz frequency EM4100 type RFID tags

They have nothing else in common, not even manufacturer or relationship, for example one is not a successor of the other.

The [RDM630 is produced by SeeedStudio and costs between $10-$15](https://www.seeedstudio.com/125Khz-RFID-module-UART-p-171.html), you'll find technical details of the [125Khz RFID module - UART](http://wiki.seeedstudio.com/125Khz_RFID_module-UART/) on their wiki.

While the [RDM6300 is an affordable alternative, costing between $1-$3](https://www.aliexpress.com/w/wholesale-rdm6300.html) depending on where you source it.

However, please note that there is a performance difference between the two which explains the significant price difference.

Fortunately, as both the RDM630 and RDM6300 have the same pin layout, the wiring and code should be exactly the same.

## Wiring

### P1

| Pin | Label  |
| --- | ------ |
| 1   | TX     |
| 2   | RX     |
| 3   | -      |
| 4   | GND    |
| 5   | +5V DC |

### P2 (antenna)

| Pin | Label |
| --- | ----- |
| 1   | ANT1  |
| 2   | ANT2  |

### P3

| Pin | Label  |
| --- | ------ |
| 1   | LED    |
| 2   | +5V DC |
| 3   | GND    |

### Arduino

Here's an example of how you may wish to wire your RDM6300 to your Arduino or compatible device (eg: ESP 8266).

| RDM6300 | Arduino    |
| ------- | ---------- |
| +5V DC  | +5V DC     |
| GND     | GND        |
| TX      | Digial Pin |

Connecting the wires:

- Connect +5V DC and GND of the module to the corresponding pins of the Arduino.
- Connect the TX to a digital pin on the Arduino, for example pin 4.

## Software

When an RFID tag is detected, the device will send a payload of 14 bytes:

| 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   | 10  | 11  | 12  | 13  | 14  |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| h   | d   | d   | d   | d   | d   | d   | d   | d   | d   | d   | c   | c   | t   |
| 2   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | 2   |

The head (h) or tx start is always 2 and the tail (t) or tx end is always 2.

The 10 digits (d) of the tag data are hexadecimal (x), which you can convert into a decimal or ASCII values.

You can then use a bitwise calculation to calculate the checksum (c) is correct.

In our example, we're most interested in the decimal as this should match what is printed on the tag.

## Also see

- [RDM630 RFID Reader Library](https://playground.arduino.cc/Main/RDM630RFIDReaderLibrary)
- [Arduino-Tutorial: How to use the RDM630/RDM6300 RFID reader
  ](https://www.mschoeffler.de/2018/01/05/arduino-tutorial-how-to-use-the-rdm630-rdm6300-rfid-reader/)
