#include "ST7565.h"

//int ledPin =  13;    // LED connected to digital pin 13

// the LCD backlight is connected up to a pin so you can turn it on & off
//#define BACKLIGHT_LED 4

// pin 9 - Serial data out (SID)
// pin 8 - Serial clock out (SCLK)
// pin 7 - Data/Command select (RS or A0)
// pin 6 - LCD reset (RST)
// pin 5 - LCD chip select (CS)
ST7565 display(12, 13, 11, 18, 10);

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

extern unsigned long pulses[8];
extern unsigned long  fixedPulsein(int pin, int timeout);




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
  display.drawstring(32, 4, "Receiver");
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

