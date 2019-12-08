#include "Start.h"

Start::Start(int buttonPin, HighScore *hSptr)
    : ButtonControledMenuOption(buttonPin), highScoreItemPtr(hSptr)
{
  gameOver = false;
  defaultLevel = 0;
  level = defaultLevel;
  score = 0;
}

void Start::printGameStats(LiquidCrystal &lcd)
{
  lcd.print("Lives:");
  lcd.print(lives);
  lcd.setCursor(7, 0);
  lcd.LiquidCrystal::write((byte)0x00);
  lcd.setCursor(0, 1);
  lcd.print("Score:");
  lcd.setCursor(6, 1);
  lcd.print(score);
  lcd.print(" Level:");
  lcd.print(level);
}

void Start::displayMenuOption(LiquidCrystal &lcd)
{
  if (level == defaultLevel) //update times so the counting is ok
    totalTime = levelIncreaseTime = millis();

  lcd.clear();
  if (gameOver == true)
  {
    lcd.print("Congratulations");
    lcd.setCursor(0, 1);
    lcd.print("Press Button");
  }
  else
  {
    printGameStats(lcd);
  }
}

bool Start::waitingEvent(bool *changedState)
{
  bool stillLoaded = true;

  if (millis() - totalTime >= 10000)
  {
    if (gameOver != true)
    {
      *changedState = true;
      gameOver = true;
    }
    //this is quite inefficient since it's redeclaring this object at every
    //function call. But using lambdas gives the code a little umpf.
    //Alternatively it could be done by declaring a private function for the class.
    auto action = [changedState, &stillLoaded, this]() -> void {
      if (score > this->highScoreItemPtr->getHighScore())
        this->highScoreItemPtr->setNewHighScore(this->score);
      this->level = this->defaultLevel;
      this->score = 0;
      this->gameOver = false;
      *changedState = true;
      stillLoaded = false;
    };

    takeActionOnButtonPressed(action);
  }

  else if (millis() - levelIncreaseTime >= 5000)
  {
    levelIncreaseTime = millis();
    level++;
    score = level * 3;
    *changedState = true;
    stillLoaded = true;
  }

  return stillLoaded;
}
