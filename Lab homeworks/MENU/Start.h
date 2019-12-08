#ifndef start_h
#define start_h

#include "HighScore.h"

class Start : public ButtonControledMenuOption
{
private:
  bool gameOver;
  const int lives = 3;
  const int maxLevel = 9;

  int level;
  int score;
  int defaultLevel;

  HighScore *const highScoreItemPtr;

  unsigned long levelIncreaseTime;
  unsigned long totalTime;

  void printGameStats(LiquidCrystal &lcd);

public:
  Start(int buttonPin, HighScore *hSptr);
  void displayMenuOption(LiquidCrystal &lcd);
  bool waitingEvent(bool *changedState);
  HighScore *getAttachedHighScoreItem() { return highScoreItemPtr; }
  void setDefaultLevel(int level)
  {
    if (level >= 0 && level <= maxLevel)
    {
      this->defaultLevel = level;
      this->level = defaultLevel;
    }
  }
  int getDefaultLevel() const { return defaultLevel; }
};

#endif
