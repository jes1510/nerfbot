#ifndef _motorDriver
#define _motorDriver

#include <Arduino.h>

struct Motor {
  int PWMPin;
  int directionPin;
  int targetSpeed = 0;
  int currentSpeed = 0;
  int direction = 1;
  bool inverted = false;
  unsigned long timer;
  
};


void motorInit(int motor1PWMPin, int motor1DirPin, int motor2PWMPin, int motor2DirPin);
void setM1(int dir, int pwm);
void setM2(int dir, int pwm);
void invertM1(bool val);
void invertM2(bool val);
void updateMotor1(void);
void updateMotor2(void);
void updateAccel(int timer, int steps);



extern int accelTimer;
extern int decelTimer;
extern int accelSteps;
extern int decelSteps;

enum accelModes{
  linear,
  expo
};

extern int accelerationMode;

#endif
