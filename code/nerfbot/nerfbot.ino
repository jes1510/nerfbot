
// Requires serial command library:  https://github.com/kroimon/Arduino-SerialCommand

//#include <SoftwareSerial.h>
//#include <PololuQik.h>
#include <SerialCommand.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//
//
//
//// If using software SPI (the default case):
#define OLED_MOSI   11
#define OLED_CLK   13
#define OLED_DC    12
#define OLED_CS    10
#define OLED_RESET 18

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#define VERSION_MAJOR 0
#define VERSION_MINOR 1

int motorErrorPin = 15;

SerialCommand sCmd;     // The demo SerialCommand object

//PololuQik2s12v10 qik(16, 17, 14);

int channelPins[8];
unsigned long pulses[8];

bool quiet = false;
bool echo = true;
bool sentFlag = false;
bool sentPrompt = false;
bool streamPulses = false;

void setup() {
  int i;
  int pin;
  
  for (i=0; i<8; i++){
    pin = i + 2;
    channelPins[i] = pin;  // Pulses are on Pins D2-D9
    pinMode(pin, INPUT);
    pulses[i] = 0;  
  }

  

  sCmd.addCommand("ver", cmdVer);
  sCmd.addCommand("pulses", cmdShowPulses);
  sCmd.addCommand("stream", cmdStream);
  sCmd.addCommand("stopstream", cmdStopStream);
  sCmd.addCommand("resetm", cmdResetMotor);
  sCmd.addCommand("readerror", cmdGetMotorError);
  
  sCmd.setDefaultHandler(unrecognized);     

  pinMode(15, INPUT);  
    
  Serial.begin(9600);
  Serial.println("NerfBot");
  Serial.println("qik 2s12v10 dual serial motor controller");
  cmdResetMotor();
 // Serial.print("Firmware version: ");
 // Serial.println(qik.getFirmwareVersion());
  Serial.println();

  display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  delay(2000);
  display.clearDisplay();

  // Clear the buffer.
}

void loop() {
  // put your main code here, to run repeatedly:
  readPulses();
    
 // if (pulses[0] == 0) Serial.println("ERROR!");
  

  if(!sentPrompt) {
    sendPrompt();
  }

  if(Serial.available()) {
       sCmd.readSerial(); 
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
//  }
  

}

int pulseToBar(unsigned long pulse) {
  pulse = constrain(pulse, 980, 1900);
  return map(pulse, 980, 1900, 0, 30);  
}

void displayPulses() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(15,0);
  display.println("Receiver");
  display.drawLine(0, 35, 127, 35, WHITE);

  int i;
  int bar;
  uint8_t color = WHITE;
  display.setTextSize(1);
  display.setTextColor(WHITE);  

  for(i=0; i<8; i++){
    display.setTextSize(1);

    display.setCursor(i * 16 + 4, 56);
    display.write(i + 1 + '0');  
    
    bar = pulseToBar(pulses[i]);
    
    if (bar>15) display.fillRect(i * 16 + 4, 35, 6, bar-15, color%2);
    else {
      int topBar, loc;
      topBar = map(bar, 0, 15, 15, 0);
      if (i==0) Serial.println(topBar);
      loc = 35-(topBar);
      display.fillRect(i * 16 + 4, 35-topBar, 6, topBar , color%2);
    }
 
  }
    display.display();
}

unsigned long fixedPulsein(int pin, int timeout) {
  int start = millis();
  unsigned long pulse = 0;
  while (pulse == 0) {
    pulse = pulseIn(pin, HIGH);

    if (millis() - start > timeout) {
 
      break;
    }
  }
  return pulse;
}

void readPulses() {
  int i = 0;
  unsigned long pulse =0;
  int start = millis();
  pulse = fixedPulsein(channelPins[i], 50);

 // Serial.print(millis() - start);
  pulses[i] = pulse;
 // Serial.print("\t");
//  Serial.println(pulse); 
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
    sprintf(line, "Nerfbot %i.%i> ", VERSION_MAJOR, VERSION_MINOR);
    Serial.println(line);
    sentPrompt = true;
  }
}

void cmdVer() {  
  char line[16];
  sprintf(line, "\tVersion: %i.%i", VERSION_MAJOR, VERSION_MINOR);
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

  if (number == 1) {
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
//  qik.init();
  sendPrompt();
}

bool getMotorError() {  
  return digitalRead(15);
}

void cmdGetMotorError() {
 // bool state;
 Serial.print("\tError Byte:");
// Serial.println(qik.getErrors(), HEX);
 sendPrompt();
}

