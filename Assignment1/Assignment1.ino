#define pulseA 0
#define pulseB 4
#define switch1 16
#define switch2 17

// A variable used to indicate whether the outputs will be connected to LEDs or the oscilloscope
unsigned char usingLEDs = 0;

// Variable declaration for pulse stream parameters
int widthA;
int initialWidthA;
int widthChangeA;
int spaceA;
int widthB;
int spaceD;
int pulseCounterMax = 17;
unsigned char disablePulseStream = 0;
unsigned char modifiedMode = 0;

// Interrupt service routines for switches 1 & 2. On call, toggle the desired variable
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

  // Set up pins 0 & 4 as outputs
  pinMode(pulseA, OUTPUT);
  pinMode(pulseB, OUTPUT);

  // Set up pins 16 & 17 as inputs with internal pullup resistors
  pinMode(switch1, INPUT_PULLUP);
  pinMode(switch2, INPUT_PULLUP);
  // Attach interrupts to the switches on the rising edge
  attachInterrupt(switch1, ISR_switch1, RISING);
  attachInterrupt(switch2, ISR_switch2, RISING);

  // Increase the length of pulse stream parameters if using LEDs
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
  // If modifiedMode (toggled by switch2) is high, C = C-3
  if (modifiedMode == 1) {pulseCounterMax = 14; }
  else { pulseCounterMax = 17; }

  //Serial.print("\n\ndisablePulseStream = "); Serial.print(disablePulseStream);
  //Serial.print("\nmodifiedMode = "); Serial.print(modifiedMode);
  //Serial.print("\npulseCounterMax = "); Serial.print(pulseCounterMax);

  // start the pulse stream only if not disabled by disablePulseStream(switch1)
  if (!disablePulseStream)
  {
    // Reset the width of the signal A pulse
    widthA = initialWidthA;

    // Pulse signal B for widthB microseconds
    digitalWrite(pulseB, HIGH);
    delayMicroseconds(widthB);
    digitalWrite(pulseB, LOW);

    //Serial.print("\npulseWidthA = "); 
    // Loop through all pulses in signal A, length depending on the status of modifiedMode(switch2)
    for (int pulseCounter = 0; pulseCounter < pulseCounterMax; pulseCounter++)
    {
      //Serial.print(widthA); Serial.print("\t");
      // Pulse signal A for widthA microseconds followed by a space of spaceA microseconds
      digitalWrite(pulseA, HIGH);
      delayMicroseconds(widthA);
      digitalWrite(pulseA, LOW);
      delayMicroseconds(spaceA);
      // Increment the width of the signal A pulse for the next loop
      widthA += widthChangeA;   
    }
    // Leave a space of spaceD microseconds
    delayMicroseconds(spaceD);
  }
}
