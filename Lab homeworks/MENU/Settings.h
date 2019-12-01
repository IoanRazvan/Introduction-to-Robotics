#ifndef settings_h
#define settings_h

#include "Start.h"

class Settings : public MenuOption
{
  private:
    Start * const startItemPtr;
    const int * const buttonPtr;
    const int * const yAxisPinPtr;
    int currentStartLevel;

    const int maxThreshold = 600;
    const int minThreshold = 400;
    bool joyMoved;
    bool swState;
    bool lastSwState;
    void readingOnYAxis(bool *);
  public:
    Settings::Settings(Start * _startPtr,const int * _buttonPtr,const int * _yAxisPinPtr) ;
    void displayMenuOption(LiquidCrystal & lcd);
    bool waitingEvent(bool *changedState);  
};

#endif
