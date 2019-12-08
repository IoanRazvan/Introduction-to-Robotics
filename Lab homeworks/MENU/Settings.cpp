#include "Settings.h"

Settings::Settings(Start *_startPtr, int buttonPin, int axisPin)
    : startItemPtr(_startPtr), ButtonControledMenuOption(buttonPin),
      SingleAxisJoystickControledMenuOption(axisPin)
{
  currentStartLevel = startItemPtr->getDefaultLevel();
}

void Settings::displayMenuOption(LiquidCrystal &lcd)
{
  lcd.clear();
  lcd.print("Starting Level: ");
  lcd.setCursor(15, 0);
  lcd.print(currentStartLevel);
}

bool Settings::waitingEvent(bool *changedState)
{
  bool stillLoaded = true;
  auto action = [this, &stillLoaded, changedState]() -> void {
    this->startItemPtr->setDefaultLevel(this->currentStartLevel);
    *changedState = true;
    stillLoaded = false;
  };

  takeActionOnButtonPressed(action);
  if (stillLoaded)
  {
    auto negativeMoved = [this, changedState]() -> void {
      this->currentStartLevel = ((this->currentStartLevel - 1) + 10) % 10;
      *changedState = true;
    };

    auto positiveMoved = [this, changedState]() -> void {
      this->currentStartLevel = (this->currentStartLevel + 1) % 10;
      *changedState = true;
    };
    takeActionsOnJoystickMoved(positiveMoved, negativeMoved);
  }
  return stillLoaded;
}
