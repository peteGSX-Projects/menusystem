#include <Arduino.h>
#include "StaticMenus.h"

void setupStaticMenus() {
  MenuItem homeScreen("Home screen", MENU, nullptr);
  MenuItem throttleList("Throttle List", MENU, &homeScreen);
  MenuItem throttle1("Setup Throttle 1", ACTION_ITEM, &throttleList);
  MenuItem throttle2("Setup Throttle 2", ACTION_ITEM, &throttleList);
  MenuItem throttle3("Setup Throttle 3", ACTION_ITEM, &throttleList);
  menuManager.addMenuItem(&homeScreen);
  

  menuManager.displayMenu();
}