
#ifndef _lcd
#define _lcd


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
#define TOPLINE 4



enum LCDPages {
  netPage,
  rxPulses,
  traffic,
  slave,
};


int pulseToBar(unsigned long pulse);
void lcdInit();
void displayPulses();
void displayStats();
void trafficMonitor();
void manageLCD(int displayPage);
void setCursor(int x, int y);
void displayNetwork();
void slavePage();

extern int cursorX;
extern int cursorY;
extern float batteryVoltage;


#endif
