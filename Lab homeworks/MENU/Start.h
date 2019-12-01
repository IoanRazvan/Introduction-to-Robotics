#ifndef start_h
#define start_h

#include "HighScore.h"

class Start : public MenuOption
{
  private:
    bool gameOver;
    const int lives = 3;
    const int maxLevel = 9;
    int level;
    int score;
    int defaultLevel;

    const int * const buttonPtr;
    HighScore * const highScoreItemPtr;
    bool swState;
    bool lastSwState;

    unsigned long levelIncreaseTime;
    unsigned long totalTime;

    void printGameStats(LiquidCrystal & lcd);
  public:
    Start(const int * buttonPtr, HighScore * hSptr);
    void displayMenuOption(LiquidCrystal & lcd);
    bool waitingEvent(bool * changedState);
    HighScore * getAttachedHighScoreItem() { return highScoreItemPtr; }
    void setDefaultLevel(int level) { if(level >= 0 && level <= maxLevel) {this->defaultLevel = level; this->level = defaultLevel;} }
    int getDefaultLevel() const { return defaultLevel; }
};

#endif
