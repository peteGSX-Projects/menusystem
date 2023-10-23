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
#include "StaticMenus.h"

/// @brief Class for each stored menu item
class MenuItem {
public:
  const char *name;
  void (*action)();
  void (*actionHold)();
  void (*actionRelease)();
  void *objectPointer;
  MenuItem *next;

  // Constructor
  MenuItem(const char *name,
            void (*action)(),
            void (*actionHold)(),
            void (*actionRelease)(),
            void *objectPointer) {
    this->name = name;
    this->action = action;
    this->actionHold = actionHold;
    this->actionRelease = actionRelease;
    this->objectPointer = objectPointer;
    this->next = nullptr;
  }
};

/// @brief Class for each submenu, inherits from MenuItem class
class Submenu : public MenuItem {
public:
  Submenu(const char *name) : MenuItem(name, nullptr, nullptr, nullptr, nullptr) {}
};

class MenuManager {
public:
  MenuManager(SSD1306AsciiSpi &display);

  /// @brief Add the provided MenuItem object to the menu manager
  /// @param item 
  void addMenuItem(MenuItem *item);

  /// @brief Display the current menu
  void displayMenu();

  /// @brief Process keypad input, called from the keypad event handler
  /// @param key char
  /// @param keyState KeyState typedef from Keypad class
  void processKeypad(char key, KeyState keyState);

private:
  SSD1306AsciiSpi &_display;
  MenuItem *_currentMenuItem;
  void _displayKeyAction(char key, KeyState keyState);

};

// End of class

// External declarations
extern Keypad keypad;
extern SSD1306AsciiSpi display;
extern MenuManager menuManager;

/// @brief Event handler for the keypad
/// @param key 
void keypadEvent(KeypadEvent key);

#endif