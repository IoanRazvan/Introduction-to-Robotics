#ifndef menu_opt_h
#define menu_opt_h

#include "Arduino.h"
#include <LiquidCrystal.h>

//MenuOption represents an interface
//it imposes that all classes implementing it
//offer the basic functionality of a menu option

//displayMenuOption is a function taking as argumnet the
//display being used to output information

//waitingEvent takes as argument a boolean variable
//indicating if the state of the class Menu that manages
//all menu option has changed, this was done so that
//Menu clears the display and redraws only when being informed 
//by the currently displayed menu option, that a change has ocured

//Also the function returns another boolean variable indicating
//if the menu option is still loaded. For example, the Start menu
//option will increase the level and score after 5 seconds 
//the information has changed so the diaplay has to be redrawn
//but the menu option should still be loaded since the game is not
//finished yet.

class MenuOption
{
  public:
    MenuOption(){}
    virtual void displayMenuOption(LiquidCrystal & c) = 0;
    virtual bool waitingEvent(bool * changedState) = 0;
};

#endif
