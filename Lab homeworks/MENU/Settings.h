#ifndef settings_h
#define settings_h

#include "Start.h"
#include "SingleAxisJoystickControledMenuOption.h"

class Settings : public ButtonControledMenuOption, public SingleAxisJoystickControledMenuOption
{
private:
  Start *const startItemPtr;
  int currentStartLevel;

public:
  Settings(Start *_startPtr, int button, int axisPin);
  void displayMenuOption(LiquidCrystal &lcd);
  bool waitingEvent(bool *changedState);
};

#endif
