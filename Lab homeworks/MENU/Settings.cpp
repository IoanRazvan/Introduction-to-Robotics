#include "Settings.h"

Settings::Settings(Start * _startPtr,const int * _buttonPtr,const int * _yAxisPinPtr) 
  : startItemPtr(_startPtr), buttonPtr(_buttonPtr), yAxisPinPtr(_yAxisPinPtr)
{
  currentStartLevel = startItemPtr->getDefaultLevel();
  joyMoved = false;
  swState = false;
  lastSwState = false;
}

void Settings::readingOnYAxis(bool * stateChanged)
{
   int yValue;
   yValue = analogRead(*yAxisPinPtr);
   if (yValue < minThreshold && joyMoved == false) {
        if (currentStartLevel > 0)
          currentStartLevel--;
        else
          currentStartLevel = 9;
        joyMoved = true;
        *stateChanged = true;
      }
   if (yValue > maxThreshold && joyMoved == false) {
         if (currentStartLevel < 9)
            currentStartLevel++;
         else
            currentStartLevel = 0;
         joyMoved = true;
         *stateChanged = true;
      }
   if (yValue >= minThreshold && yValue <= maxThreshold) {
      joyMoved = false;
}
}

void Settings::displayMenuOption(LiquidCrystal & lcd)
{
  lcd.clear();
  lcd.print("Starting Level: ");
  lcd.setCursor(15, 0);
  lcd.print(currentStartLevel);
}

bool Settings::waitingEvent(bool * changedState)
{
  bool stillLoaded = true;
  swState = digitalRead(*buttonPtr);
    if (swState != lastSwState) {
      if (swState == LOW) {
         startItemPtr->setDefaultLevel(currentStartLevel);
        *changedState = true;
        stillLoaded = false;
      }
      else
        stillLoaded = true;
    }
    else
      stillLoaded = true;
    lastSwState = swState; 
    if (stillLoaded)
      readingOnYAxis(changedState);
    return stillLoaded;
}
