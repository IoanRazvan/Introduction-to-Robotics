const int analogInputPin0 = A0;
const int analogInputPin1 = A1;
const int analogInputPin2 = A2;

const int analogOutputPin9 = 9;
const int analogOutputPin10 = 10;
const int analogOutputPin11 = 11;

int potValueOutputPin9;
int redLedValue;

int potValueOutputPin10;
int greenLedValue;

int potValueOutputPin11;
int blueLedValue;

void setup() {
  
  pinMode(analogInputPin0, INPUT);
  pinMode(analogInputPin1, INPUT);
  pinMode(analogInputPin2, INPUT);
  
  pinMode(analogOutputPin10, OUTPUT);
  pinMode(analogOutputPin11, OUTPUT);
  pinMode(analogOutputPin9, OUTPUT);
  
}

void loop() {
  
  potValueOutputPin11 = analogRead(analogInputPin0);
  redLedValue = map(potValueOutputPin11, 0, 1023, 0, 255);
  
  potValueOutputPin10 = analogRead(analogInputPin1);
  greenLedValue = map(potValueOutputPin10, 0, 1023, 0, 255);

  potValueOutputPin9 = analogRead(analogInputPin2);
  blueLedValue = map(potValueOutputPin9, 0, 1023, 0, 255);
  
  analogWrite(analogOutputPin11, redLedValue);
  analogWrite(analogOutputPin10, greenLedValue);
  analogWrite(analogOutputPin9, blueLedValue);
  
}
