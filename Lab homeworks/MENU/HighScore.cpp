#include "HighScore.h"
#include <EEPROM.h>

HighScore::HighScore(int * buttonPtr) : buttonPtr(buttonPtr)
{
  //if EEMPROM has a "not been medled with" value, than initialize holder and highScore with default or given values
  if (EEPROM.read(0) == 0xFF) {
    this->holder = new char[strlen(max_char_in_name) + 1];
    strncpy(this->holder, "No Name", max_char_in_name + 1);
    this->holder[max_char_in_name] = '\0';
    this->highScore = 0;
  }
  //else load the highScore from EEPROM
  else {
    int addr = 0;
    highScore = EEPROM.read(addr);
    int name_len = 0;
    for (addr = 1; EEPROM.read(addr) != 0xFF; addr++)
      name_len++;
    this->holder = new char[name_len];
    for (addr = 1; addr < name_len + 1; addr++)
      this->holder[addr - 1] = EEPROM.read(addr);
  }
}

HighScore::~HighScore()
{
  delete [] holder;
}

void HighScore::saveChangesToEEPROM()
{
  int addr = 0;
  EEPROM.write(addr, highScore);
  for (addr = 1; addr < strlen(holder) + 2; addr++)
    EEPROM.write(addr, holder[addr - 1]);
}

void HighScore::setNewHolderName(const char * newName)
{
  //change holder's name
  delete [] holder;
  this->holder = new char[strlen(max_char_in_name) + 1];
  strncpy(this->holder, newName, max_char_in_name + 1);
  this->holder[max_char_in_name] = '\0';

  //save changes to EEPROM
  saveChangesToEEPROM();
}

void HighScore::setNewHighScore(int newScore)
{
  //if newScore is viable for a highScore change and save to EEPROM
  if (newScore > highScore && newScore < max_score)
  {
    highScore = newScore;
    saveChangesToEEPROM();
  }
}

bool HighScore::waitingEvent(bool *changedState)
{
  bool stillLoaded = true;

  swState = digitalRead(*buttonPtr);
  if (swState != lastSwState) {
    if (swState == LOW) {
      stillLoaded = false;
      *changedState = true;
    }
    else 
      stillLoaded = true;
  }
  else 
    stillLoaded = true;
  lastSwState = swState;
  return stillLoaded;
}

void HighScore::displayMenuOption(LiquidCrystal & lcd)
{
  lcd.clear();
  lcd.print(holder);
  lcd.setCursor(0, 1);
  lcd.print(highScore);
}
