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

#include <Arduino.h>
#include "MenuSystem.h"

/***********************************************************************************
Set up our keypad
***********************************************************************************/
char keys[4][3] = {
 {'1', '2', '3'},
 {'4', '5', '6'},
 {'7', '8', '9'},
 {'*', '0', '#'}
};
byte pin_rows[4] = {KEYPAD_PIN2, KEYPAD_PIN7, KEYPAD_PIN6, KEYPAD_PIN4};
byte pin_column[3] = {KEYPAD_PIN3, KEYPAD_PIN1, KEYPAD_PIN5};
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, 4, 3);
bool keyPress = false;

/***********************************************************************************
Set up our display
***********************************************************************************/
SSD1306AsciiSpi display;

/***********************************************************************************
Instantiate the menu system
***********************************************************************************/
MenuSystem menuSystem(display);

/***********************************************************************************
MenuItem public methods
***********************************************************************************/
// Constructor
MenuItem::MenuItem(const char *name, MenuItemType type, void (*action)(void*), void *objectPointer)
    : name(name), type(type), action(action), objectPointer(objectPointer), next(nullptr) {}




/***********************************************************************************
MenuItem private methods
***********************************************************************************/

/***********************************************************************************
MenuSystem public methods
***********************************************************************************/
// Constructor
MenuSystem::MenuSystem(SSD1306AsciiSpi &display)
  : _display(display), _currentMenu(nullptr), _currentMenuItem(nullptr) {}

void MenuSystem::begin() {
  _display.begin(OLED_TYPE, CS_PIN, DC_PIN);
  _displayStartupInfo();
}

void MenuSystem::addSubmenu(MenuSystem &submenu, const char *name) {

}

void MenuSystem::addItem(const char *name, MenuItemType type, void (*action)(void*), void *object) {
  MenuItem *newItem = new MenuItem(name, type, action, object);
  if (_currentMenuItem) {
    _currentMenuItem->next = newItem;
  } else {
    _currentMenuItem = newItem;
  }
}

void MenuSystem::processKeypad(char key, KeyState keyState) {
  switch (keyState) {
    case PRESSED:
      keyPress = true;
      break;
    case HOLD:
      keyPress = false;
      _displayKeyAction(key, HOLD);
      break;
    case RELEASED:
      if (keyPress) {
        _displayKeyAction(key, PRESSED);
      } else {
        _displayKeyAction(key, RELEASED);
      }
      break;
    default:
      break;
  }
}

/***********************************************************************************
MenuSystem private methods
***********************************************************************************/
void MenuSystem::_displayStartupInfo() {
  _display.clear();
  _display.setCursor(0, 0);
  _display.setFont(OLED_FONT);
  _display.print(F("Menu testing"));
}

void MenuSystem::_displayKeyAction(char key, KeyState keyState) {
  _display.setCursor(0, 2);
  _display.clearToEOL();
  _display.print(key);
  switch (keyState) {
    case PRESSED:
      _display.print(F(" pressed"));
      break;
    case HOLD:
      _display.print(F(" held"));
      break;
    case RELEASED:
      _display.print(F(" released"));
      break;
    default:
      break;
  }
}

void keypadEvent(KeypadEvent key) {
  KeyState keyState = keypad.getState();
  menuSystem.processKeypad(key, keyState);
}
