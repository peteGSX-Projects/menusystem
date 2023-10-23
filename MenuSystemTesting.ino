#include <Arduino.h>
#include "MenuSystem.h"
#include "StaticMenus.h"

void setup() {
  Serial.begin(115200);
  keypad.addEventListener(keypadEvent);
  keypad.setHoldTime(KEYPAD_HOLD);
  menuSystem.begin();
  setupStaticMenus();
}

void loop() {
  keypad.getKey();
}