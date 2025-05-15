// blink.ino
// Button works as on off for all lights

#include <TinyWireM.h>

#define ioExpanderAddress 0x20
#define buttonPin 1

unsigned long lastPress = 0;
unsigned long debounce = 500;

int state = 0;

void setup() {
  TinyWireM.begin();
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  updateState();
  if (state == 0) {
    TinyWireM.beginTransmission(ioExpanderAddress);
    TinyWireM.write(0b11111111);
    TinyWireM.endTransmission();
  } else {
    TinyWireM.beginTransmission(ioExpanderAddress);
    TinyWireM.write(0b00000000);
    TinyWireM.endTransmission();
  }
}

void updateState() {
  int currentButtonState = digitalRead(buttonPin);
  if (currentButtonState == LOW && millis() > lastPress + debounce) {
    state == 0 ? state = 1 : state = 0;
    lastPress = millis(); 
  }
}
