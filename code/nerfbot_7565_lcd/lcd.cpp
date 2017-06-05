#include <ST7565.h>
#include "motorDriver.h"
#include "lcd.h"
#include "cli.h"
#include "platform.h"

extern SerialCommand sCmd;     // The demo SerialCommand object


//int ledPin =  13;    // LED connected to digital pin 13

// the LCD backlight is connected up to a pin so you can turn it on & off
//#define BACKLIGHT_LED 4

// pin 12 - Serial data out (SID)
// pin 13 - Serial clock out (SCLK)
// pin 11 - Data/Command select (RS or A0)
// pin 18 - LCD reset (RST)
// pin 10 - LCD chip select (CS)

ST7565 display(MOSI, SCK, A0, LCDRESET, NSS);


int pulseToBar(unsigned long pulse) {
  pulse = constrain(pulse, 980, 1900);
  return map(pulse, 980, 1900, 0, 30);
}

void lcdInit() {
  display.begin(0x08);
  delay(500);
  display.clear();
}


void displayPulses() {
  display.clear();
  display.drawstring(32, TOPLINE, "Receiver");
  display.drawline(0, 0, 127, 0, BLACK);

  int i;
  int bar;

  for(i=0; i<8; i++){
    display.drawchar(i * 16 + 4,3, i + 1 + '0');
    bar = pulseToBar(pulses[i]);

    if (bar>15) display.fillrect(i * 16 + 4, 1, 6, bar-15, BLACK);
    else {
      int topBar, loc;
      topBar = map(bar, 0, 15, 15, 0);
      loc = 64-(topBar);
      display.fillrect(i * 16 + 4, 63-topBar, 6, topBar+1 , BLACK);
    }
  }
    display.display();
}


void displayStats() {
  display.clear();
  display.drawstring(32, TOPLINE, "Motor Status");
    display.drawline(0, 42, 127, 42, BLACK);
  char line[32];
  char label[16];
  int i;
  struct Motor* pMotor ;

  for (i=0; i<2; i++) {
    if (i == 0) pMotor = &motor1;
    else if (i == 1) pMotor = &motor2;
    sprintf(line, "M:%d S:%d  D:%i  I:%i ", i + 1,
                                                             pMotor->targetSpeed,
                                                             pMotor->direction,
                                                            pMotor->inverted);
    sprintf(label, "Motor %d", i);
  //display.drawstring(0, 5 + i, "label");
  display.drawstring(0, 6 + i, line);
  }
  display.display();

}

void trafficMonitor() {
  display.clear();
  display.drawstring(20, 4, "Serial Traffic");
  display.drawline(0, 42, 127, 42, BLACK);
  display.drawstring(0, 6, sCmd.publicBuffer);
  //Serial.println(sCmd.publicBuffer);
  display.display();

}


void manageLCD(int displayPage) {
    if (displayPage == motorStats) displayStats();
    if (displayPage == rxPulses) displayPulses();
    if (displayPage == traffic) trafficMonitor();
}
