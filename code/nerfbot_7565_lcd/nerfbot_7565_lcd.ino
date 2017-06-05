#include <Arduino.h>
#include "lcd.h";
#include "cli.h";
#include <SerialCommand.h>
#include "platform.h"

// Requires serial command library:  https://github.com/kroimon/Arduino-SerialCommand


#include "motorDriver.h";
#include "nerfbot.h";

int VERSION_MAJOR = 0;
int VERSION_MINOR = 1;

int displayPage = motorStats;
int driveMode = serial;

unsigned long currentTime = millis();
unsigned long lastTime = millis();



void setup() {
  int i;
  int pin;

//  for (i=0; i<7; i++){
 //   pinMode(channelPins[i], INPUT);
 //   pulses[i] = 0;  
 // }
  
  Serial.begin(9600);
  Serial.println("STM32 Smart Motor Controller");
  Serial.println();
  lcdInit();
  cmdInit();
  
  motorInit(M1PWMPIN, M1DIRPIN, M2PWMPIN, M2DIRPIN);  // 1PWM, 1DIR, 2PWM, 2DIR

  pinMode(5, OUTPUT);
  
  

}

void loop() {

 // readPulses();

  if(!sentPrompt) {
    sendPrompt();
  }

  if(Serial.available()) {
    readCMD();
  }

  manageLCD(displayPage);
 // setM1(1, 64);
 // setM2(1, 64);

 
 updateMotor1();
 updateMotor2();

digitalWrite(3, HIGH);



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

