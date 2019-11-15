const int inputBuzzerPin = A0;
const int outputBuzzerPin = 8;
const int pushButtonPin = 2;

const int soundThreshold = -1; //since the input buzzer didn't work and the analog input pin A0 was constantly reading a value of 0
const int waitingTime = 5000;  //I set the threshold at -1 to check that the code was working fine 


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
