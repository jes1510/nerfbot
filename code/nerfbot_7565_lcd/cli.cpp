#include "cli.h"
//#include "motorDriver.h"
#include <SerialCommand.h>
#include "lcd.h"
//#include "nerfbot.h"

SerialCommand sCmd;     // The demo SerialCommand object
int cliMode = ackOnly;
char IP[] = "xxx.xxx.xxx.xxx";
char wiiStatus[] = "Booting...";


void cmdInit() {
  sCmd.addCommand("ver", cmdVer);
  sCmd.addCommand("pulses", cmdShowPulses);
  sCmd.addCommand("stream", cmdStream);
  sCmd.addCommand("stopstream", cmdStopStream);
  sCmd.addCommand("print", cmdPrint);
  sCmd.addCommand("cursor", cmdCursor);
  sCmd.addCommand("ip", cmdIP);
  sCmd.addCommand("page", cmdPage);
  sCmd.addCommand("wii", cmdWiiStatus);
  sCmd.addCommand("batv", cmdBattery);
  sCmd.setDefaultHandler(unrecognized);
}



void sendPrompt() {
  if(cliMode == interactive) {
    char line[16];
    sprintf(line, "Nerfbot %i.%i> ", VERSION_MAJOR, VERSION_MINOR);
    Serial.println(line);
    
  }

  else Serial.println("OK");
  sentPrompt = true;
}

void cmdVer() {
  char line[16];
  sprintf(line, "\tVersion: %i.%i", VERSION_MAJOR, VERSION_MINOR);
  Serial.println(line);
  sendPrompt();
}

void cmdShowPulses() {
  printPulses();
  sendPrompt();
}

// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command) {
  if (cliMode == interactive) {
    Serial.print("\tUNKNOWN COMMAND: ");
    Serial.println(command);
    sendPrompt();
  }

  else Serial.println("ERROR");
}



void cmdStream() {
  int number;
  char *arg;
  arg = sCmd.next();
  number = atoi(arg);

  if (number == 1) {
    streamPulses = true;
  }

  else {
    streamPulses = false;
    sendPrompt();
    }
}



void cmdStopStream() {
  streamPulses = false;
  sendPrompt();
}

unsigned long remap(unsigned long pulse) {
  pulse = constrain(pulse, 980, 1900);
  return map(pulse, 980, 1900, -127, 127);

}



void printPulses() {
  int i;
  char line[128];
  sprintf(line, "\tCH1: %lu  CH2: %lu  CH3: %lu  CH4: %lu  CH5: %lu  CH6: %lu  CH7: %lu  CH8: %lu",
              pulses[0], pulses[1], pulses[2], pulses[3], pulses[4], pulses[5], pulses[6], pulses[7]);
  Serial.println(line);
}

void readCMD() {
  sCmd.readSerial();
}






void setCLIMode(int mode) {  
}

void cmdCursor() {
  int x, y;
  char *arg1, *arg2;
  arg1 = sCmd.next();
  arg2 = sCmd.next();
  x = atoi(arg1);
  y = atoi(arg2);
  setCursor(x, y);  
}

void cmdPrint() {
}

void cmdIP() { 
  char *arg;
  arg = sCmd.next();
  strncpy(IP, arg, sizeof(IP));
  sendPrompt();
}

void cmdWiiStatus() {
  char *arg;
  arg = sCmd.next();
  strncpy(wiiStatus, arg, sizeof(wiiStatus));  
  sendPrompt();

}

void cmdPage() {
  char *arg;  
  arg = sCmd.next();
}

void cmdBattery() {
  Serial.println(batteryVoltage);
  sendPrompt();
}

