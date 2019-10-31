const int analogInputPin0 = A0;
const int analogInputPin1 = A1;
const int analogInputPin2 = A2;

const int analogOutputPin11 = 11;
const int analogOutputPin10 = 10;
//const int analogOutputPin;

int potValueOutputPin10;
int ledValueOutputPin10;

int potValueOutputPin11;
int ledValueOutputPin11;

//int potValue;
//int ledValue;

void setup() {
  Serial.begin(9600);
  
  pinMode(analogInputPin0, INPUT);
  pinMode(analogInputPin1, INPUT);
  
  pinMode(analogOutputPin10, OUTPUT);
  pinMode(analogOutputPin11, OUTPUT);
}

void loop() {
  potValueOutputPin10 = analogRead(analogInputPin0);
  ledValueOutputPin10 = map(potValueOutputPin10, 0, 1023, 0, 255);
  
  potValueOutputPin11 = analogRead(analogInputPin1);
  ledValueOutputPin11 = map(potValueOutpuPin11, 0, 1023, 0, 255);
  
  analogWrite(analogOutputPin11, ledValue1);
  analogWrite(analogOutputPin10, ledValue0);
 
}
