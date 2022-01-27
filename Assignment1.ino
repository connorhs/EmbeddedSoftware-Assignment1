#define pulseA 0
#define pulseB 4
#define switch1 16
#define switch2 17

int widthA = 80000;
int widthChangeA = 50000;
int spaceA = 10000;
int widthB = 10000;
int pulseCounterMax = 17;
unsigned char disablePulseStream = 1;
unsigned char modifiedMode = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pulseA, OUTPUT);
  pinMode(pulseB, OUTPUT);
}

void loop() {
    
  widthA = 80000;
  
  if (modifiedMode == 1) {pulseCounterMax = 14; }
  else { pulseCounterMax = 17; }
  
  digitalWrite(pulseB, HIGH);
  delayMicroseconds(widthB);
  digitalWrite(pulseB, LOW);

  for (int pulseCounter = 0; pulseCounter <= pulseCounterMax; pulseCounter++)
  {
    digitalWrite(pulseA, HIGH);
    delayMicroseconds(widthA);
    digitalWrite(pulseA, LOW);
    delayMicroseconds(spaceA);
    widthA += widthChangeA;
    delayMicroseconds(45000);    
  }
}
