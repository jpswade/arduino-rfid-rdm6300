#include "Arduino.h"
#include "SoftwareSerial.h"
#include <string.h>

int rxPin = 4;
int txPin = 5;
int serialSpeed = 9600;
static const int STX = 2;
static const int ETX = 3;

byte _data[6];

typedef enum {
  WAITING_FOR_STX,
  READING_DATA,
  DATA_VALID
} state;
state _s;

int nibble;
byte AsciiCharToNum(byte data);

SoftwareSerial rfid(rxPin, txPin);

void setup()
{
  Serial.begin(serialSpeed);
  rfid.begin(serialSpeed);
}

void loop()
{
  byte data[6];
  byte length;

  if (rfidAvailable()) {
    getData(data, length);
    Serial.print("Hex tag: ");
    for (int i = 0; i < length; i++) {
      Serial.print(data[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
    // Concatenate the bytes in the data array to one long rendered as a decimal.
    unsigned long result =
      ((unsigned long int)data[1] << 24) +
      ((unsigned long int)data[2] << 16) +
      ((unsigned long int)data[3] << 8) +
      data[4];
    Serial.print("Decimal tag: ");
    Serial.println(result);
  }
}

void getData(byte* data, byte& length) {
  length = sizeof(_data);
  memcpy(data, _data, sizeof(_data));
}

bool rfidAvailable() {
  if (rfid.available() > 0)
  {
    _s = dataParser(_s, rfid.read());
    return (_s == DATA_VALID);
  }
  return false;
}

state dataParser(state s, byte c) {
  switch (s) {
    case WAITING_FOR_STX:
    case DATA_VALID:
      if (c == STX) {
        nibble = -1;
        return READING_DATA;
      }
      break;
    case READING_DATA:
      if (++nibble < 12) {
        _data[nibble >> 1] = ((nibble & 0x1) == 0 ? AsciiCharToNum(c) << 4 : _data[nibble>>1] + AsciiCharToNum(c));
        return READING_DATA;
      }
      if (c != ETX) { // Expected end character, but got something else.
        return WAITING_FOR_STX;
      }
      for (int i = 0; i < 5; i++) {
        _data[5] ^= _data[i];
      }
      if (_data[5] != 0) { // Checksum doesn't match.
        return WAITING_FOR_STX;
      }
      return DATA_VALID;
    default:
      return WAITING_FOR_STX;
  }
  return WAITING_FOR_STX;
}

byte AsciiCharToNum(byte data) {
  return (data > '9' ? data - '0' - 7 : data - '0');
}

