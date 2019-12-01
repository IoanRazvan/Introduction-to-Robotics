#ifndef highscore_h
#define highscore_h

#include "MenuOption.h"

class HighScore : public MenuOption
{
  private:
    const int max_score = 54;
    const int max_char_in_name = 10;
    int highScore;
    char * holder;

    const int * const buttonPtr;
    int swState;
    int lastSwState;
    void saveChangesToEEPROM();
  public:
    HighScore(int * buttonPtr);
    ~HighScore();
    void setNewHolderName(const char * newName);
    int getHighScore() const { return highScore; }
    void setNewHighScore(int newScore);
    void displayMenuOption(LiquidCrystal & c);
    bool waitingEvent(bool * changedState);
};

#endif
