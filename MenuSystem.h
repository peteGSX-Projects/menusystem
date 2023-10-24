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

/// @brief Determines the valid key processing and display methods for the item
enum MenuItemType {
  MENU,         // Displays columnar menu items with keypad to select, paginated with #
  ACTION_ITEM,  // Perform the associated action when selected
  INPUT_ITEM,   // Display input screen and perform action on #
};

/// @brief Class for each stored menu item
class MenuItem {
public:
  const char *name;
  MenuItemType menuItemType;
  MenuItem *parent;
  void (*action)();
  void (*actionHold)();
  void (*actionRelease)();
  void *objectPointer;
  MenuItem *next;

  // Constructor
  /// @brief Constructor for a new menu item
  /// @param name
  /// @param menuItemType
  /// @param parent
  /// @param action
  /// @param actionHold
  /// @param actionRelease
  /// @param objectPointer
  MenuItem(const char *name,
            MenuItemType menuItemType,
            MenuItem *parent,
            void (*action)() = nullptr,
            void (*actionHold)() = nullptr,
            void (*actionRelease)() = nullptr,
            void *objectPointer = nullptr) {
    this->name = name;
    this->menuItemType = menuItemType;
    this->parent = parent;
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
  Submenu(const char *name) : MenuItem(name, MENU, nullptr, nullptr, nullptr, nullptr, nullptr) {}
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

  /// @brief Retrieve the count of items associated with the menu
  /// @return 
  int getItemCount();

private:
  SSD1306AsciiSpi &_display;
  MenuItem *_currentMenuItem;

  /// @brief Temporary function to display they key pressed and its state
  /// @param key 
  /// @param keyState 
  void _displayKeyAction(char key, KeyState keyState);

  /// @brief Display the home screen
  void _displayHomeScreen();

  /// @brief Display all menu items
  void _displayMenuItems();

  /// @brief Display input screen to capture numeric input
  void _displayInputScreen();

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