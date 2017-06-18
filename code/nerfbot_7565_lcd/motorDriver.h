#ifndef _motorDriver
#define _motorDriver

#include <Arduino.h>

struct Motor {
  int PWMPin;
  int direction1Pin;
  int direction2Pin;
  int targetSpeed = 0;
  int currentSpeed = 0;
  int direction = 1;
  bool inverted = false;
  unsigned long timer;
  
};


void motorInit(int motor1PWMPin, int motor1Dir1Pin, int motor1Dir2Pin, int motor2PWMPin, int motor2Dir1Pin, int motor2Dir2Pin);
void setM1(int dir, int pwm);
void setM2(int dir, int pwm);
void invertM1(bool val);
void invertM2(bool val);
void updateMotor1(void);
void updateMotor2(void);
void updateAccel(int timer, int steps);
void setMotor1Speed(int pwm);
void setMotor2Speed(int pwm);



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
