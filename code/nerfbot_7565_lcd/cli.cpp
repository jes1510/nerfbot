#include "cli.h"
#include "motorDriver.h"
#include <SerialCommand.h>

SerialCommand sCmd;     // The demo SerialCommand object


void cmdInit() {
  sCmd.addCommand("ver", cmdVer);
  sCmd.addCommand("pulses", cmdShowPulses);
  sCmd.addCommand("stream", cmdStream);
  sCmd.addCommand("stopstream", cmdStopStream);
  sCmd.addCommand("resetm", cmdResetMotor);
  sCmd.addCommand("readerror", cmdGetMotorError);
  sCmd.addCommand("debug", cmdDebug);
  sCmd.addCommand("invert1", cmdInvert1);
  sCmd.addCommand("invert2", cmdInvert2);
  sCmd.addCommand("stats", printMotorStats);
  sCmd.addCommand("motor1", cmdMotor1);
  sCmd.addCommand("motor2", cmdMotor2);
  sCmd.addCommand("setLinear", cmdSetLinear);
  sCmd.addCommand("setExpo", cmdSetExpo);
  sCmd.addCommand("setAccel", cmdSetAccel);
  sCmd.addCommand("getAccel", cmdGetAccel);
  sCmd.setDefaultHandler(unrecognized);
}



void sendPrompt() {
  if(!quiet) {
    char line[16];
    sprintf(line, "Nerfbot %i.%i> ", VERSION_MAJOR, VERSION_MINOR);
    Serial.println(line);
    sentPrompt = true;
  }
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
  Serial.print("\tUNKNOWN COMMAND: ");
  Serial.println(command);
  sendPrompt();
}

void cmdDebug() {
  int number;
  char *arg;
  arg = sCmd.next();
  number = atoi(arg);
  Serial.print(number);
  if (number == 1)  {
    debug = true;
    Serial.println("Debug Mode ENABLED!");
  }
  else {
    debug = false;
    Serial.println("Debug Mode DISABLED");
  }
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

void cmdResetMotor () {
  digitalWrite(14, LOW);
  delay(500);
  digitalWrite(14, HIGH);
  delay(250);
//  qik.init();
  sendPrompt();
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


bool getMotorError() {
  return digitalRead(15);
}

void cmdGetMotorError() {
 // bool state;
 Serial.print("\tError Byte:");
// Serial.println(qik.getErrors(), HEX);
 sendPrompt();
}

void cmdInvert1() {
  int number;
  char *arg;
  arg = sCmd.next();
  number = atoi(arg);

  if (number==1) invertM1(true);
  else invertM1(false);
  sendPrompt();

}

void cmdInvert2() {
  int number;
  char *arg;
  arg = sCmd.next();
  number = atoi(arg);

  if (number==1) invertM2(true);
  else invertM1(false);
  Serial.println(number);
  sendPrompt();

}

void printMotorStats() {
  int number;
  char *arg;
  char line[64];
  arg = sCmd.next();
  number = atoi(arg);
  struct Motor* pMotor ;

  if (number == 1) pMotor = &motor1;
  else if (number == 2) pMotor = &motor2;
  else {
    Serial.println("\t Error: Invalid Motor Number");
    sendPrompt();
    return;
  }
  
  sprintf(line, "\tMotor: %d  Spd: %d  Dir: %i  Inv: %i ", number,
                                                           pMotor->targetSpeed,
                                                           pMotor->direction,
                                                           pMotor->inverted);
  Serial.println(line);
  sendPrompt();
}

void cmdMotor1() {
  int spd, dir; 
  char *arg1, *arg2;

  arg1 = sCmd.next();
  arg2 = sCmd.next();

  spd = atoi(arg1);
  dir = atoi(arg2);  

  setM1(dir, spd);   
  
  char line[32];
  sprintf(line, "Motor1   Speed: %d    Dir: %d", spd, dir);  
  Serial.println(line);
  sendPrompt();
  
}


void cmdMotor2() {
  int spd, dir; 
  char *arg1, *arg2;

  arg1 = sCmd.next();
  arg2 = sCmd.next();

  spd = atoi(arg1);
  dir = atoi(arg2);  

  setM2(dir, spd);   
  
  char line[32];
  sprintf(line, "Motor2   Speed: %d    Dir: %d", spd, dir);  
  Serial.println(line);
  sendPrompt();
  
}

void cmdSetExpo() {
  accelerationMode = expo;
  Serial.print("\tAcceleration Mode is now: ");
  Serial.println(accelerationMode);
  sendPrompt();
}

void cmdSetLinear() {
  accelerationMode = linear;
  Serial.print("\tAcceleration Mode is now: ");
  Serial.println(accelerationMode);
  sendPrompt();
}

void cmdSetAccel() {
  int timer, steps; 
  char *arg1, *arg2;

  arg1 = sCmd.next();
  arg2 = sCmd.next();

  timer = atoi(arg1);
  steps = atoi(arg2);  

  updateAccel(timer, steps);  
  sendPrompt();
  
}

void cmdGetAccel() {
  int i;
  char line[128];
  sprintf(line, "\tAcceleration settings ->  Timer: %d    Steps: %d", accelTimer, accelSteps);
  Serial.println(line);
  sendPrompt();
}

