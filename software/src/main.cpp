#include <Arduino.h>
#include <DMXSerial.h>

#define DAC_MAX_VALUE 4095
#define DAC_MIN_VALUE 0
#define DMX_MAX_VALUE 255

// SPI Pins for DAC
const int CSPin = 4;
const int SCKPin = 3;
const int MOSIPin = 2;

// DIP switch pins for DMX address 
const int DMX0 = 6;
const int DMX1 = 7;
const int DMX2 = 8;
const int DMX3 = 9;
const int DMX4 = 10;
const int DMX5 = 11;
const int DMX6 = 12;
const int DMX7 = 16;
const int DMX8 = 15;
const int DMXfunc = 14;

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
  // SPI
  pinMode(CSPin, OUTPUT);
  pinMode(SCKPin, OUTPUT);
  pinMode(MOSIPin, OUTPUT);
  digitalWrite(CSPin, HIGH);
  //DMX
  pinMode(DMX0, INPUT);
  pinMode(DMX1, INPUT);
  pinMode(DMX2, INPUT);
  pinMode(DMX3, INPUT);
  pinMode(DMX4, INPUT);
  pinMode(DMX5, INPUT);
  pinMode(DMX6, INPUT);
  pinMode(DMX7, INPUT);
  pinMode(DMX8, INPUT);
  DMXSerial.init(DMXReceiver);
}

void loop() {
  uint16_t DMXChannel = !digitalRead(DMX0) + (!digitalRead(DMX1) << 1) + (!digitalRead(DMX2) << 2) + (!digitalRead(DMX3) << 3) + (!digitalRead(DMX4) << 4) + (!digitalRead(DMX5) << 5) + (!digitalRead(DMX6) << 6)+ (!digitalRead(DMX7) << 7) + (!digitalRead(DMX8) << 8);
  setDac((DAC_MAX_VALUE / DMX_MAX_VALUE) * DMXSerial.read(DMXChannel));
  delay(4);
} 