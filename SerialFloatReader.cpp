#include "SerialFloatReader.h"

float readSerialFloat() {
  union {
    char chars[4];
    float floatResult;
  } converter;

  // Buffer that store the bytes
  char buffer[4];

  // Read into the buffer
  Serial.readBytes(buffer, 4);

  // Map the buffer bytes into the converter
  for (int i = 0; i < 4; i++) {
    converter.chars[i] = buffer[i];
  }

  // Snag the result as a float
  return converter.floatResult;
}