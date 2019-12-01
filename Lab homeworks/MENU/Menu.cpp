#include "Menu.h"

Menu::Menu(Start * s, Settings * se, HighScore * hs) : options{s, se, hs}, loadedItem(false), stateChanged(false), current_position(0)
{
}

void Menu::menuDisplay(LiquidCrystal & lcd)
{
  lcd.clear();
  lcd.print(" Start  Settings");
  lcd.setCursor(0, 1);
  lcd.print(" Highscore");
  lcd.setCursor(arrow_position[current_position].col, arrow_position[current_position].lin);
  lcd.print(">");
}

void Menu::displayMenu(LiquidCrystal & lcd)
{
  stateChanged = false;
  if (loadedItem)
    options[current_position]->displayMenuOption(lcd);
  else 
    menuDisplay(lcd);
}

void Menu::waitingEvent()
{
  loadedItem = options[current_position]->waitingEvent(&stateChanged);
}
