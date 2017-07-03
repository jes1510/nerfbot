#ifndef _cli
#define _cli

#include <SerialCommand.h>

extern char IP[16];
extern char wiiStatus[16];

enum cliModes {
  interactive,
  quiet,
  ackOnly,
  debug
};

extern int cliMode;

void cmdVer();
void cmdShowPulses();
void cmdStream();
void cmdStopStream();

void unrecognized(const char *command);
void printPulses();
void cmdDebug();

void cmdCursor();
void cmdPrint();
void cmdIP();
void cmdPage();
void cmdWiiStatus();
void cmdBattery();

//extern bool quiet;
extern bool echo;
extern bool sentFlag;
extern bool sentPrompt;
extern bool streamPulses;
//extern bool debug;

extern int VERSION_MAJOR;
extern int VERSION_MINOR;
extern unsigned long pulses[8];
extern unsigned long fixedPulsein(int pin, int timeout);
extern float batteryVoltage;

void cmdInit();
void sendPrompt();
void cmdVer();
void cmdShowPulses();
void unrecognized(const char *command);
void cmdStream();
void cmdStopStream();
unsigned long remap(unsigned long pulse);

void printPulses();
bool getMotorError();

void readCMD();



#endif
