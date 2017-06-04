#ifndef _motorDriver
#define _motorDriver

#include <Arduino.h>

struct Motor {
  int PWMPin;
  int directionPin;
  int speed = 128;
  int direction = 1;
  bool inverted = false;
};


void motorInit(int motor1PWMPin, int motor1DirPin, int motor2PWMPin, int motor2DirPin);
void setM1(int dir, int pwm);
void setM2(int dir, int pwm);
void invertM1(bool val);
void invertM2(bool val);
void updateMotor1(void);
void updateMotor2(void);


extern int gunRelay;



#endif
