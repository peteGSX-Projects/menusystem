#include <Arduino.h>
#include "MenuSystem.h"

void setup() {
  Serial.begin(115200);
  menuSystem.begin();
}

void loop() {
  menuSystem.loop();
}