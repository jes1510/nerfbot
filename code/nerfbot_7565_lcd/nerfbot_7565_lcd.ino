
// Requires serial command library:  https://github.com/kroimon/Arduino-SerialCommand

//#include <SoftwareSerial.h>
//#include <PololuQik.h>
#include "motorDriver.h";


struct buff;

int  VERSION_MAJOR = 0;
int  VERSION_MINOR = 1;

int motorErrorPin = 15;

extern Motor motor1;
extern Motor motor2;

unsigned long pulses[8];

bool quiet = false;
bool echo = true;
bool sentFlag = false;
bool sentPrompt = false;
bool streamPulses = false;
bool debug = false;

int channel = 0;

int channelPins[] = {4,5,6,7,9};

extern void cmdResetMotor();
extern void lcdInit();
extern void sendPrompt();
extern void readCMD();
extern void printPulses();
extern void displayPulses();
extern void cmdInit();
extern void displayStats();
extern void trafficMonitor();
extern void manageLCD(int page);

int displayPage = 2;

void setup() {
  int i;
  int pin;

  for (i=0; i<7; i++){
    pinMode(channelPins[i], INPUT);
    pulses[i] = 0;  
  }
  
  Serial.begin(9600);
  Serial.println("STM32 Smart Motor Controller");
  Serial.println();
  lcdInit();
  cmdInit();
  motorInit(15, 16, 17,  18);
  

}

void loop() {
  readPulses();

  if(!sentPrompt) {
    sendPrompt();
  }

  if(Serial.available()) {
    readCMD();
  }

  manageLCD(displayPage);

}




void readPulse(int channel) {
  unsigned long pulse;
  pulse = fixedPulsein(channelPins[channel], 25);
  pulses[channel] = pulse;
  if (debug) {
    Serial.print(channel);
    Serial.print(": ");
    Serial.println(pulse);
    Serial.println();
  }
}

void readPulses() {
  int i;
  unsigned long pulse =0;
  int start = millis();
  for (i=0; i<6; i++){  
    pulse = fixedPulsein(channelPins[i], 30);

  if (debug)  {  
    Serial.print("Elapsed mS: ");
    Serial.println(millis() - start);
  }
    
  pulses[i] = pulse;
  if(debug) {
 
    Serial.print("Channel: ");
    Serial.print(i);
    Serial.print("\t\tPulse: ");
    Serial.println(pulse);
    Serial.println(); 
    
    Serial.print("\t");
    Serial.println(pulse); 
    }
  }
}


void(* resetFunc) (void) = 0; //declare reset function @ address 0



unsigned long fixedPulsein(int pin, int timeout) {
  int start = millis();
  unsigned long pulse = 0;
  int elapsed = 0;
  while (pulse == 0) {
    pulse = pulseIn(pin, HIGH, 25000);
    elapsed = millis() - start;
    if (elapsed > timeout) {
      if (debug) {
      Serial.print("pin: ");
      Serial.print(pin);
      Serial.print("\t\t");
      Serial.print(elapsed);
      Serial.println("\t---> TIMEOUT!");
      }
      break;
    }
  }
  return pulse;
}

