#include <Arduino.h>

struct Motor {
  int PWMPin;
  int directionPin;
  int speed = 255;
  int direction = 1;
  bool inverted = false;
};


void motorInit(int motor1PWMPin, int motor1DirPin, int motor2PWMPin, int motor2DirPin);
void setM1(int dir, int pwm);
void setM2(int dir, int pwm);
void invertM1(bool val);
void invertM2(bool val);
