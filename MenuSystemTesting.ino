#include <Arduino.h>
#include "MenuSystem.h"
#include "StaticMenus.h"

void setup() {
  Serial.begin(115200);
  Serial.println(F("Menu System testing"));
  keypad.addEventListener(keypadEvent);
  keypad.setHoldTime(KEYPAD_HOLD);
  display.begin(OLED_TYPE, CS_PIN, DC_PIN);
  setupStaticMenus();
  menuManager.displayMenu();
}

void loop() {
  keypad.getKey();
}