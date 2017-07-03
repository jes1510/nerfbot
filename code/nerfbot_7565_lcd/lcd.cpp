#include <ST7565.h>

#include "lcd.h"
#include "cli.h"
#include "platform.h"
#include <avr/dtostrf.h>

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
int cursorX = 0;
int cursorY = 0;


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


void trafficMonitor() {
  display.clear();
  display.drawstring(20, 4, "Serial Traffic");
  display.drawline(0, 42, 127, 42, BLACK);
  display.drawstring(0, 6, sCmd.publicBuffer);
  display.display();

}


void manageLCD(int displayPage) {
    if (displayPage == rxPulses) displayPulses();
    if (displayPage == traffic) trafficMonitor();
    if (displayPage == netPage) displayNetwork();
}


void setCursor(int x, int y) {
  cursorX = x;
  cursorY = y;
}

void print(char &message) {


}

void displayNetwork() {
  char line[16];  
  char voltStr[6];
  
  display.clear();
  display.drawstring(30, 4, "Networking");
  display.drawline(0, 42, 127, 42, BLACK);
  display.drawstring(4, 6, "IP: ");
  display.drawstring(24, 6, IP);
  display.drawstring(4, 7, "Wii: ");
  display.drawstring(35, 7, wiiStatus); 
  dtostrf(batteryVoltage, 2, 1, voltStr);
  sprintf(line, "Battery: %sv", voltStr);
  display.drawstring(4, 1, line);  
  display.display();
  
}


