
#ifndef _lcd
#define _lcd


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
#define TOPLINE 4

//extern Motor motor2;
//extern Motor motor1;
//extern SerialCommand sCmd;

enum LCDPages {
  motorStats,
  rxPulses,
  traffic,
};


int pulseToBar(unsigned long pulse);
void lcdInit();
void displayPulses();
void displayStats();
void trafficMonitor();
void manageLCD(int displayPage);

#endif
