#include <Arduino.h>
#include "StaticMenus.h"

MenuManager menuManager(display);
bool keyPress = false;


void setupStaticMenus() {
  MenuItem homeScreen("Home screen", nullptr);
  Submenu menu1("Menu 1", &homeScreen);
  Submenu menu2("Menu 2", &homeScreen);
  menuManager.addMenuItem(&homeScreen);
  menuManager.addMenuItem(&menu1);
  menuManager.addMenuItem(&menu2);
  menuManager.displayMenu();
}


void getMinimumFreeMemory() {
  noInterrupts(); // Disable interrupts to get volatile value 
  int retval = freeMemory();
  interrupts();
  Serial.print(F("Free RAM: "));
  Serial.println(retval);
}

extern "C" char* sbrk(int incr);

int freeMemory() {
  char top;
  return (int)(&top - reinterpret_cast<char *>(sbrk(0)));
}

void keypadEvent(KeypadEvent key) {
  // getMinimumFreeMemory();
  KeyState keyState = keypad.getState();
  switch (keyState) {
    case PRESSED:
      keyPress = true;
      break;
    case HOLD:
      keyPress = false;
      menuManager.handleInput(key, HOLD);
      break;
    case RELEASED:
      if (keyPress) {
        menuManager.handleInput(key, PRESSED);
      } else {
        menuManager.handleInput(key, RELEASED);
      }
      break;
    default:
      break;
  }
}