#ifndef _nerfbot
#define _nerfbot


#include <Arduino.h>
#include "motorDriver.h";


struct buff;

//int  VERSION_MAJOR;
//int  VERSION_MINOR;

extern Motor motor1;
extern Motor motor2;

// PWM 6, 10
// PWM Dont work:  12, 3, 5

unsigned long pulses[8];


// Flags for state machines
bool quiet = false;
bool echo = true;
bool sentFlag = false;
bool sentPrompt = false;
bool streamPulses = false;
bool debug = false;

int channel = 0;
//int channelPins[] = {CH0Pin, CH1Pin, CH2Pin, CH3Pin};

extern int displayPage;

enum driveModes {
  RC,
  serial
};

//Platform





#endif
