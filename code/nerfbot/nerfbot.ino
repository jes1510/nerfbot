
#include <SoftwareSerial.h>
#include <PololuQik.h>

PololuQik2s12v10 qik(10, 11, 13);

int channelPins[8];
unsigned long pulses[8];


void setup() {

  int i;
  for (i=0; i<8; i++){
    channelPins[i] = i+2;  // Pulses are on Pins D2-D9
    pulses[i] = 0;
  }

  
  Serial.begin(9600);
  Serial.println("qik 2s12v10 dual serial motor controller");
  
  qik.init();
  
  Serial.print("Firmware version: ");
  Serial.write(qik.getFirmwareVersion());
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  readPulses();
  printPulses();
  delay(100);

}

void readPulses() {
  int i;
  for (i=0; i<8; i++){
    pulses[i] = pulseIn(channelPins[i], HIGH, 25000);
  }  
}

void printPulses() {
  int i;
  char line[64];
  sprintf(line, "CH1: %lu  CH2: %lu", pulses[0], pulses[1]);
  Serial.println(line);

}

