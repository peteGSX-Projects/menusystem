/*
 *  © 2023 Peter Cole
 *
 *  This file is for a serially connected throttle for a DCC-EX EX-CommandStation.
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this code.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H

#include <Arduino.h>
#include "defines.h"
#include <SPI.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiSpi.h"
#include "Keypad.h"

enum MenuItemType {
  SUBMENU,
  ACTION_ITEM,
  USER_INPUT,
};

class Menu;

class MenuItem {
public:
  MenuItem(const char *name, MenuItemType type, void (*action)(void*), void (*actionHold)(void*), void (*actionRelease)(void*), void *objectPointer, Menu *parentMenu);
  const char *name;
  MenuItemType type;
  void (*action)(void*);
  void (*actionHold)(void*);
  void (*actionRelease)(void*);
  void *objectPointer;
  Menu *parentMenu;
  MenuItem *next;

};

class Menu {
public:
  // Menu(SSD1306AsciiSpi &display, Keypad &keypad);
  Menu(SSD1306AsciiSpi &display);
  void begin();
  void addSubmenu(Menu &submenu, const char *name);
  void addItem(const char *name, MenuItemType type, void (*action)(void*), void (*actionHold)(void*), void (*actionRelease)(void*), void *object, Menu *parentMenu);
  void processKeypad(char key, KeyState keyState);

private:
  SSD1306AsciiSpi &_display;
  Menu *_currentMenu;
  MenuItem *_currentMenuItem;
  void _displayStartupInfo();
  void _displayHomeScreen();
  void _displayKeyAction(char key, KeyState keyState);
  void _displayMenu();
  void _displayInputScreen();

};

// End of class

extern Menu menuSystem;
extern Keypad keypad;
extern SSD1306AsciiSpi display;

void keypadEvent(KeypadEvent key);

#endif