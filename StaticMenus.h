#ifndef STATICMENUS_H
#define STATICMENUS_H

#include <Arduino.h>
#include "MenuSystem.h"

extern "C" char *sbrk(int incr);

extern MenuManager menuManager;

void setupStaticMenus();
void getMinimumFreeMemory();
int freeMemory();

/// @brief Event handler for the keypad
/// @param key 
void keypadEvent(KeypadEvent key);

#endif