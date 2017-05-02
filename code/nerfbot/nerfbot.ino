
// Requires serial command library:  https://github.com/kroimon/Arduino-SerialCommand

#include <SoftwareSerial.h>
#include <PololuQik.h>
#include <SerialCommand.h>

int versionMajor = 0;
int versionMinor = 1;

SerialCommand sCmd;     // The demo SerialCommand object



PololuQik2s12v10 qik(10, 11, 13);

int channelPins[8];
unsigned long pulses[8];

bool quiet = false;
bool echo = true;
bool sentFlag = false;
bool sentPrompt = false;
bool streamPulses = false;

#define SERIALCOMMAND_DEBUG


void setup() {

  int i;
  for (i=0; i<8; i++){
    channelPins[i] = i+2;  // Pulses are on Pins D2-D9
    pulses[i] = 0;  
  }

  sCmd.addCommand("ver", cmdVer);
  sCmd.addCommand("pulses", cmdShowPulses);
  sCmd.addCommand("stream", cmdStream);
  sCmd.addCommand("stopstream", cmdStopStream);
  sCmd.addCommand("resetm", cmdResetMotor);
  
  sCmd.setDefaultHandler(unrecognized);      // Handler for command that isn't matched  (says "What?")
  
  Serial.begin(9600);
  Serial.println("NerfBot");
  Serial.println("qik 2s12v10 dual serial motor controller");
  qik.init();  
 // Serial.print("Firmware version: ");
 // Serial.println(qik.getFirmwareVersion());
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  readPulses();

  if(!sentPrompt) {
    sendPrompt();
  }

  if(Serial.available()) {
       sCmd.readSerial(); 
  }

  if (streamPulses) printPulses();

  qik.setM0Speed(remap(pulses[0]));
  qik.setM1Speed(remap(pulses[1]));

}

void readPulses() {
  int i;
  for (i=0; i<8; i++){
    pulses[i] = pulseIn(channelPins[i], HIGH, 25000);
  }  
}

void printPulses() {
  int i;
  char line[128];
  sprintf(line, "\tCH1: %lu  CH2: %lu  CH3: %lu  CH4: %lu  CH5: %lu  CH6: %lu  CH7: %lu  CH8: %lu", 
              pulses[0], pulses[1], pulses[2], pulses[3], pulses[4], pulses[5], pulses[6], pulses[7]);
  Serial.println(line);
}

void sendPrompt() {
  if(!quiet) {
    char line[16];
    sprintf(line, "Nerfbot %i.%i> ", versionMajor, versionMinor);
    Serial.print(line);
    sentPrompt = true;
  }
}

void cmdVer() {  
  char line[16];
  sprintf(line, "\tVersion: %i.%i", versionMajor, versionMinor);
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

void cmdStream() { 
  int number;
  char *arg;
  arg = sCmd.next();

  number = atoi(arg);

  if (number) {
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
  qik.init();
  sendPrompt();

}



