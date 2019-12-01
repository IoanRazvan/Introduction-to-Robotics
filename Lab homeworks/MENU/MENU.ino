#include "Menu.h"

byte heart[] = {
  B00000,
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};

const int RS = 12;
const int enable = 11;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
const int pinY = A1;
const int pinX = A0;
const int pinSw = 7;

bool joyMoved = false;
bool swState = false;
bool lastSwState = false;

int minThreshold = 400;
int maxThreshold = 600;

int xValue = 0;
int yValue = 0;

LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);
HighScore h(&pinSw);
Start s(&pinSw, &h);
Settings se(&s, &pinSw, &pinX);
Menu m(&s, &se, &h);

void readingOnXAxis() {
  xValue = analogRead(pinY);
  if (xValue < minThreshold && joyMoved == false) {
    m.setArrowPos(m.getArrowPos() - 1);
    joyMoved = true;
  }
  if (xValue > maxThreshold && joyMoved == false) {
    m.setArrowPos(m.getArrowPos() + 1);
    joyMoved = true;
  }
  if (xValue >= minThreshold && xValue <= maxThreshold) {
    joyMoved = false;
  }
}

void setup() {
  lcd.begin(16, 2);
  pinMode(pinSw, INPUT_PULLUP);
  pinMode(pinY, INPUT);
  pinMode(pinX, INPUT);
  m.displayMenu(lcd);
  lcd.createChar(0, heart);
  Serial.begin(9600);
}

void loop() {
  if (m.isLoaded() == false)
  {
    readingOnXAxis();
  }

  if (m.isLoaded() == false)
  {
    swState = digitalRead(pinSw);
    if (swState != lastSwState) {
      if (swState == LOW)
        m.Load();
    }
    lastSwState = swState;
  }

  if (m.getState())
     m.displayMenu(lcd);
  if (m.isLoaded() == true)
    m.waitingEvent();
 if (m.getState() == true)
  m.displayMenu(lcd);
}
