#ifndef _cli
#define _cli

#include <SerialCommand.h>
#include "motorDriver.h"

extern Motor motor1;
extern Motor motor2;

void cmdVer();
void cmdShowPulses();
void cmdStream();
void cmdStopStream();
void cmdResetMotor();
void cmdGetMotorError();
void unrecognized(const char *command);
void printPulses();
void cmdDebug();
void cmdInvert1();
void cmdInvert2();
void printMotorStats();
void cmdMotor1();
void cmdMotor2();



extern bool quiet;
extern bool echo;
extern bool sentFlag;
extern bool sentPrompt;
extern bool streamPulses;
extern bool debug;

extern int VERSION_MAJOR;
extern int VERSION_MINOR;
extern unsigned long pulses[8];
extern unsigned long fixedPulsein(int pin, int timeout);

void cmdInit();
void sendPrompt();
void cmdVer();
void cmdShowPulses();
void unrecognized(const char *command);
void cmdDebug();
void cmdStream();
void cmdStopStream();
unsigned long remap(unsigned long pulse);
void cmdResetMotor();
void printPulses();
bool getMotorError();
void cmdGetMotorError();
void cmdInvert1();
void cmdInvert2();
void printMotorStats();
void readCMD();
void cmdSetExpo();
void cmdSetLinear();
void cmdSetAccel();
void cmdGetAccel();


#endif
