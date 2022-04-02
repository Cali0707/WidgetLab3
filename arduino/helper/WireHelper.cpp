#include <Wire.h>

void readFromWire(char *dest, int num) {
  int i = 0;
  while (i < num) {
    dest[i] = (char)Wire.read();
    i++;
  }
  dest[i] = 0;
}

void sendMessage(const char* message, int address) {
  Wire.beginTransmission(address);
  Wire.write(message);
  Wire.endTransmission();
}
