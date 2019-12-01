#ifndef menu_opt_h
#define menu_opt_h

#include "Arduino.h"
#include <LiquidCrystal.h>


class MenuOption
{
  public:
    MenuOption(){}
    virtual void displayMenuOption(LiquidCrystal & c) = 0;
    virtual bool waitingEvent(bool * changedState) = 0;
};

#endif
