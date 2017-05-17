
// Requires serial command library:  https://github.com/kroimon/Arduino-SerialCommand

//#include <SoftwareSerial.h>
//#include <PololuQik.h>


int  VERSION_MAJOR = 0;
int  VERSION_MINOR = 1;

int motorErrorPin = 15;


//PololuQik2s12v10 qik(16, 17, 14);

//int channelPins[8];

unsigned long pulses[8];

bool quiet = false;
bool echo = true;
bool sentFlag = false;
bool sentPrompt = false;
bool streamPulses = false;
bool debug = false;

int channel = 0;

int channelPins[] = {2,4,5,6,7,8,9};

extern void cmdResetMotor();
extern void lcdInit();
extern void sendPrompt();
extern void readCMD();
extern void printPulses();
extern void displayPulses();
extern void cmdInit();

void readPulses();

void setup() {
  int i;
  int pin;
  
  for (i=0; i<7; i++){
    pinMode(channelPins[i], INPUT);
    pulses[i] = 0;  
  }


  pinMode(15, INPUT);  
    
  Serial.begin(9600);
  Serial.println("NerfBot");
  Serial.println("qik 2s12v10 dual serial motor controller");
  cmdResetMotor();
 // Serial.print("Firmware version: ");
 // Serial.println(qik.getFirmwareVersion());
  Serial.println();
  lcdInit();
  cmdInit();
  

}

void loop() {

  readPulses();

  if(!sentPrompt) {
    sendPrompt();
  }

  if(Serial.available()) {
    readCMD();
  }
     
  if (streamPulses) printPulses();

  displayPulses();

//  qik.setM0Speed(remap(pulses[0]));
//  qik.setM1Speed(remap(pulses[1]));
//  if(digitalRead(motorErrorPin)==HIGH) {   
//      Serial.println("\n\tMOTOR ERROR!");
//      cmdResetMotor();
//      sendPrompt();
//      delay(250);    
 // }
  

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
  for (i=0; i<8; i++){  
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
