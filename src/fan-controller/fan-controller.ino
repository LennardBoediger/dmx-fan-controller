#include <DMXSerial.h>
#define FAN_PIN_1 10
#define FAN_PIN_2 11

uint16_t DMX_Channel = 1; // TODO: Add Dip Switch Selection

void setup() {
  DMXSerial.init(DMXReceiver);

  // PWM Outputs
  pinMode(FAN_PIN_1, OUTPUT);
  pinMode(FAN_PIN_2, OUTPUT);

  // Set Default Fan Speed to 0 
  DMXSerial.write(DMX_Channel, 0);
}

void loop() {
  analogWrite(FAN_PIN_1, DMXSerial.read(DMX_Channel));
  analogWrite(FAN_PIN_2, DMXSerial.read(DMX_Channel));
}
