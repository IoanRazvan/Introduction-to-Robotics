#include "Start.h"

Start::Start(const int * buttonPtr, HighScore * hSptr)
  : buttonPtr(buttonPtr), highScoreItemPtr(hSptr)
{
  swState = false;
  lastSwState = false;
  gameOver = false;
  defaultLevel = 0;
  level = defaultLevel;
  score = level * 3;
}

void Start::printGameStats(LiquidCrystal & lcd)
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

void Start::displayMenuOption(LiquidCrystal & lcd)
{
  if (level == defaultLevel) //initialize time keeper varaibles
    totalTime = levelIncreaseTime = millis();
  
  lcd.clear();
  if (gameOver == true)
  {
    lcd.print("congratulations");
    lcd.setCursor(0, 1);
    lcd.print("Press Button");
  }
  else
  {
    printGameStats(lcd);
  }
}

bool Start::waitingEvent(bool * changedState)
{
  bool stillLoaded;

  if (millis() -  totalTime >= 10000)
  {
    if (gameOver != true)
    {
      *changedState = true;
      gameOver = true;
    }
    
    swState = digitalRead(*buttonPtr);
    if (swState != lastSwState) {
      if (swState == LOW) {
         if (score > highScoreItemPtr->getHighScore())
            highScoreItemPtr->setNewHighScore(score);
        level = defaultLevel;
        score = 0;
        gameOver = false;
        *changedState = true;
        stillLoaded = false;
      }
      else
        stillLoaded = true;
    }
    else
      stillLoaded = true;
    lastSwState = swState;
  }

  else if (millis() - levelIncreaseTime >= 5000)
  {
    levelIncreaseTime = millis();
    level++;
    score = level * 3;
    *changedState = true;
    stillLoaded = true;
  }

  else *changedState = false;
  
  return stillLoaded;
}
