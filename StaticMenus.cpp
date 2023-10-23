#include <Arduino.h>
#include "StaticMenus.h"

void setupStaticMenus() {
  Menu menu1(display);
  menu1.addItem("Test", ACTION_ITEM, nullptr, nullptr, nullptr, nullptr, &menu1);
}