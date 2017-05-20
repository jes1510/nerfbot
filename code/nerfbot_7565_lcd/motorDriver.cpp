#include "motorDriver.h"

Motor motor1;
Motor motor2;


void motorInit(int motor1PWMPin, int motor1DirPin, int motor2PWMPin, int motor2DirPin) {    
  motor1.PWMPin = motor1PWMPin;
  motor1.directionPin = motor1DirPin;
  motor2.PWMPin = motor2PWMPin;
  motor2.directionPin = motor2DirPin;

  pinMode (motor1.PWMPin, OUTPUT);
  pinMode (motor1.directionPin, OUTPUT);
  pinMode (motor2.PWMPin, OUTPUT);
  pinMode (motor2.directionPin, OUTPUT);  
}


void setM1(int dir, int pwm) {
  motor1.speed = pwm;
  motor1.direction = dir;  
  analogWrite(motor1.PWMPin, pwm); 
  if(motor1.inverted == true) dir = dir * -1;
  digitalWrite(motor1.directionPin, dir);  
}


void setM2(int dir, int pwm) {
  motor2.speed = pwm;
  motor2.direction = dir;  
  analogWrite(motor2.PWMPin, pwm); 

  if(motor2.inverted == true) dir = dir * -1;
  digitalWrite(motor2.directionPin, dir);
  
}

void invertM1(bool val) {
  motor1.inverted = val;
}

void invertM2(bool val) {
  motor2.inverted = val;
}



