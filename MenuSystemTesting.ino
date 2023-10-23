#include <Arduino.h>
#include "MenuSystem.h"

void setup() {
  Serial.begin(115200);
  menuSystem.begin();
  keypad.addEventListener(keypadEvent);
  keypad.setHoldTime(KEYPAD_HOLD);
}

void loop() {
  keypad.getKey();
}