#include <Arduino.h>

#define DAC_MAX_VALE 1024*4-1

// SPI Pins for DAC
const int CSPin = 4;
const int SCKPin = 3;
const int MOSIPin = 2;

// This function transmits data via SPI to the DAC (MCP4922)
// WRITE COMMAND REGISTER FOR MCP4922 (12-BIT DAC):
// Bit 15: channel (A=0, B=1), 
// Bit 14: Buffer (default=0), 
// Bit 13: Gain (1x=1, 2x=0), 
// Bit 12: shutdown (active=1. inactive-0),
// Bit 11-0: DAC Input Data bits.
// p. 24
void setDac(unsigned long value){ 
  unsigned long dacRegister = 0b0011000000000000;
  // Set channel A
  dacRegister &= ~(1 << 15);
  // Generate the two bytes that will be sent to the DAC
  unsigned long dacSendBytes = dacRegister | value;

  // Start SPI transmission
  digitalWrite(CSPin, LOW); 
  for(int i = 0; i < 16; i++){
    digitalWrite(MOSIPin, bitRead(dacSendBytes, 15-i));
    delay(2);
    digitalWrite(SCKPin, HIGH);
    delay(2);
    digitalWrite(SCKPin, LOW);
  }
  digitalWrite(CSPin, HIGH);
}

void setup() {
  pinMode(CSPin, OUTPUT);
  pinMode(SCKPin, OUTPUT);
  pinMode(MOSIPin, OUTPUT);
  digitalWrite(CSPin, HIGH);
}

void loop() {
  setDac(DAC_MAX_VALE);
  delay(4);
}