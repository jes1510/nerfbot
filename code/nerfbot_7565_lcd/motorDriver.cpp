#include "motorDriver.h"
#include "platform.h"

Motor motor1;
Motor motor2;

int channelPins[] = {CH0PIN,CH1PIN,CH2PIN,CH3PIN};

int motor1CurrentSpeed;
int motor2CurrentSpeed;
int motor1TargetSpeed;
int motor2TargetSpeed;

int accelTimer = 50;
int decelTimer = 100;
int accelSteps = 25;

int accelerationMode = linear; 

// 1PWM, 1DIR, 2PWM, 2DIR
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
  if (pwm > 252) pwm = 252;
  motor1.targetSpeed = pwm;
  motor1.direction = dir;  
  analogWrite(motor1.PWMPin, pwm); 
  if(motor1.inverted == true) dir = dir * -1;
  digitalWrite(motor1.directionPin, dir);  
}


void setM2(int dir, int pwm) {
  if (pwm > 252) pwm = 252;  
  motor2.targetSpeed = pwm;
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


void updateMotor1(void) {
  motor1.targetSpeed = constrain(motor1.targetSpeed, 0, 252);  
  digitalWrite(motor1.directionPin, motor1.direction); 
  if (millis() - motor1.timer > accelTimer) {
    
    if (motor1.targetSpeed > motor1.currentSpeed) {
      
      if (accelerationMode == linear) motor1.currentSpeed += accelSteps;
      else if (accelerationMode == expo) motor1.currentSpeed = pow(2, motor1.currentSpeed);
      motor1.currentSpeed = constrain(motor1.currentSpeed, 0, 252);
      analogWrite(motor1.PWMPin, motor1.currentSpeed);      
     // Serial.print("Updated: ");
    //  Serial.println(motor1.currentSpeed);
      motor1.timer = millis();
    }
  

   if (motor1.targetSpeed < motor1.currentSpeed) {
      motor1.currentSpeed -= accelSteps;
      motor1.currentSpeed = constrain(motor1.currentSpeed, 0, 252);
      analogWrite(motor1.PWMPin, motor1.currentSpeed);
      
     // Serial.print("Updated: ");
    //  Serial.println(motor1.currentSpeed);
      motor1.timer = millis();
    }
  }  
 }
    



void updateMotor2(void) {
  motor2.targetSpeed = constrain(motor2.targetSpeed, 0, 252);  
  digitalWrite(motor2.directionPin, motor2.direction); 
  if (millis() - motor2.timer > accelTimer) {
    
    if (motor2.targetSpeed > motor2.currentSpeed) {
      if (accelerationMode == linear) motor2.currentSpeed += accelSteps;
      else if (accelerationMode == expo) motor2.currentSpeed = pow(2, motor2.currentSpeed);
      motor2.currentSpeed = constrain(motor2.currentSpeed, 0, 252);
      analogWrite(motor2.PWMPin, motor2.currentSpeed);      
      //Serial.print("Updated: ");
    //  Serial.println(motor2.currentSpeed);
      motor2.timer = millis();
    }
  

   if (motor2.targetSpeed < motor2.currentSpeed) {
      //if (accelerationMode == linear) motor2.currentSpeed -= accelSteps;
      motor2.currentSpeed -= accelSteps;
      motor2.currentSpeed = constrain(motor2.currentSpeed, 0, 252);
      analogWrite(motor2.PWMPin, motor2.currentSpeed);
      
     // Serial.print("Updated: ");
    //  Serial.println(motor1.currentSpeed);
      motor2.timer = millis();
    }
  }  
 }
   

void updateCurrentM1Speed(int pwm) {
  motor1.currentSpeed = pwm;
}

void updateCurrentM2Speed(int pwm) {
  motor2.currentSpeed = pwm;
}

void updateAccel(int timer, int steps) {
  accelTimer = timer;
  accelSteps = steps;
}


