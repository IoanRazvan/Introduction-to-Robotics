const int pinA = 12;
const int pinB = 8;
const int pinC = 5;
const int pinD = 3;
const int pinE = 2;
const int pinF = 11;
const int pinG = 6;
const int pinDP = 4;
const int pinD1 = 7;
const int pinD2 = 9;
const int pinD3 = 10;
const int pinD4 = 13;
const int pinSW = 1;
const int pinX = A0;
const int pinY = A1;

const int segSize = 8;
const int noOfDisplays = 4;
const int noOfDigits = 10;

int swState = LOW;
int lastSwState = LOW;
int dpState = LOW;
int decimalPointState = LOW;

int xValue = 0;
int yValue = 0;

bool joyMoved = false;

int minThreshold = 400;
int maxThreshold = 600;

unsigned long lastBlinkTime = 0;
int currentDisplay = 0;

int dig1, dig2, dig3, dig4;
int digitOnEachDisplay[noOfDisplays] = {
  dig1, dig2, dig3, dig4
};

int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

int digits[noOfDisplays] = {
  pinD1, pinD2, pinD3, pinD4
};

byte digitMatrix[noOfDigits][segSize - 1] = {
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void displayNumber(byte digit, byte decimalPoint) {
  for (int i = 0; i < segSize - 1; i++) {
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }
  digitalWrite(segments[segSize - 1], decimalPoint);
}

void showDigit(int num) {
  for (int i = 0; i < noOfDisplays; i++) {
    digitalWrite(digits[i], HIGH);
  }
  digitalWrite(digits[num], LOW);
}

void readingOnXAxis() {
   xValue = analogRead(pinY);
   if (xValue < minThreshold && joyMoved == false) {
        if (currentDisplay > 0)
          currentDisplay--;
        else
          currentDisplay = 3;
        joyMoved = true;
      }
   if (xValue > maxThreshold && joyMoved == false) {
         if (currentDisplay < 3)
            currentDisplay++;
         else
            currentDisplay = 0;
         joyMoved = true;
      }
   if (xValue >= minThreshold && xValue <= maxThreshold) {
         joyMoved = false;
      }
}

void readingOnYAxis() {
   yValue = analogRead(pinX);
   if (yValue < minThreshold && joyMoved == false) {
        if (digitOnEachDisplay[currentDisplay] > 0)
          digitOnEachDisplay[currentDisplay]--;
        else
          digitOnEachDisplay[currentDisplay] = 9;
        joyMoved = true;
      }
   if (yValue > maxThreshold && joyMoved == false) {
        if (digitOnEachDisplay[currentDisplay] < 9)
          digitOnEachDisplay[currentDisplay]++;
        else
          digitOnEachDisplay[currentDisplay] = 0;
        joyMoved = true;
      }
   if (yValue >= minThreshold && yValue <= maxThreshold) {
        joyMoved = false;
      }
}


void setup() {
  for (int i = 0; i < segSize; i++)
    pinMode(segments[i], OUTPUT);
    
  for (int i = 0; i < noOfDisplays; i++)
    pinMode(digits[i], OUTPUT);
    
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(pinSW, INPUT_PULLUP);
}

void loop() {
  swState = digitalRead(pinSW);

  if (swState != lastSwState) {
    if (swState == LOW)
      dpState = !dpState;
  }
  lastSwState = swState;
  
  
  if (dpState == LOW)
    readingOnXAxis();
  else
    readingOnYAxis();

  int digit = 0;
  while (digit < 4) {
   if (digit == currentDisplay) {
     if (millis() - lastBlinkTime >= 100 && dpState == LOW) {
         decimalPointState = !decimalPointState;
         lastBlinkTime = millis();
     }
     else if (dpState == HIGH)
       decimalPointState = HIGH;
      displayNumber(digitOnEachDisplay[digit], decimalPointState);
    }
    else
      displayNumber(digitOnEachDisplay[digit], LOW);
    showDigit(digit);
    delay(4);
    digit++;
  }
}
