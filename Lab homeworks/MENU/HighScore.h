#ifndef highscore_h
#define highscore_h

#include "ButtonControledMenuOption.h"

class HighScore : public ButtonControledMenuOption
{
private:
  //per class constants
  static const int max_score = 54;
  static const int max_char_in_name = 10;
  //current highScorer information
  int highScore;
  char *holder;

  void saveChangesToEEPROM();

public:
  HighScore(int buttonPtr);
  ~HighScore();
  void setNewHolderName(const char *newName);
  int getHighScore() const { return highScore; }
  void setNewHighScore(int newScore);
  void displayMenuOption(LiquidCrystal &c);
  bool waitingEvent(bool *changedState);
};

#endif
