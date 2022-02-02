#define pulseA 0
#define pulseB 4
#define switch1 16
#define switch2 17

unsigned char usingLEDs = 1;

int widthA;
int initialWidthA;
int widthChangeA;
int spaceA;
int widthB;
int spaceD;
int pulseCounterMax = 17;
unsigned char disablePulseStream = 0;
unsigned char modifiedMode = 0;

void IRAM_ATTR ISR_switch1() {
  if (disablePulseStream == 1) { disablePulseStream = 0; }
  else { disablePulseStream = 1; }
}

void IRAM_ATTR ISR_switch2() {
  if (modifiedMode == 1) { modifiedMode = 0; }
  else { modifiedMode = 1; }
}

void setup() {

  Serial.begin(9600);

  pinMode(pulseA, OUTPUT);
  pinMode(pulseB, OUTPUT);

  pinMode(switch1, INPUT_PULLUP);
  pinMode(switch2, INPUT_PULLUP);
  attachInterrupt(switch1, ISR_switch1, RISING);
  attachInterrupt(switch2, ISR_switch2, RISING);

  if (usingLEDs == 1)
  {
    initialWidthA = 800000;
    widthChangeA = 50000;
    spaceA = 100000;
    widthB = 50000;
    spaceD = 4500000;
  }
  else 
  {
    initialWidthA = 800;
    widthChangeA = 50;
    spaceA = 100;
    widthB = 50;
    spaceD = 4500;
  }
}

void loop() 
{  
  if (modifiedMode == 1) {pulseCounterMax = 14; }
  else { pulseCounterMax = 17; }

  Serial.print("\n\ndisablePulseStream = "); Serial.print(disablePulseStream);
  Serial.print("\nmodifiedMode = "); Serial.print(modifiedMode);
  Serial.print("\npulseCounterMax = "); Serial.print(pulseCounterMax);
  
  if (!disablePulseStream)
  {
    widthA = initialWidthA;
    
    digitalWrite(pulseB, HIGH);
    delayMicroseconds(widthB);
    digitalWrite(pulseB, LOW);

    Serial.print("\npulseWidthA = "); 
    for (int pulseCounter = 0; pulseCounter < pulseCounterMax; pulseCounter++)
    {
      Serial.print(widthA); Serial.print("\t");
      digitalWrite(pulseA, HIGH);
      delayMicroseconds(widthA);
      digitalWrite(pulseA, LOW);
      delayMicroseconds(spaceA);
      widthA += widthChangeA;   
    }
    delayMicroseconds(spaceD);
  }
}
