const int inputBuzzerPin = A0;
const int outputBuzzerPin = 8;
const int pushButtonPin = 2;

const int soundThreshold = 2; 
const int waitingTime = 5000;  


bool soundDetected = false;
bool isSound = false;

int valueAtInputBuzzer;
int buttonState;

unsigned long start;
unsigned long current;


void setup() {
 
  pinMode(inputBuzzerPin, INPUT);
  pinMode(outputBuzzerPin, OUTPUT);
  pinMode(pushButtonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  
  if (!soundDetected) {
    valueAtInputBuzzer = analogRead(inputBuzzerPin);
    if (valueAtInputBuzzer > soundThreshold) {
      start = millis();
      soundDetected = true;
    }
  }
  
  if (soundDetected) {
    current = millis();
    if (current - start >= waitingTime) {
      isSound = true;
      tone(outputBuzzerPin, 1023);
    }
  }
  
  if (isSound) {
    buttonState = !digitalRead(pushButtonPin);
    if (buttonState == 1) {
      isSound = false;
      soundDetected = false;
      noTone(outputBuzzerPin);
    }
  }
}
