#ifndef _platform
#define _platform

// General pin definitions for various bit of hardware

// Motor Control Pins
#define M1PWMPIN PB10
#define M1DIR1PIN PC10
#define M1DIR2PIN PC12
#define M2PWMPIN PC7
#define M2DIR1PIN PA13
#define M2DIR2PIN PA14

// RC Receiver
#define CH0PIN 4
#define CH1PIN 5
#define CH2PIN 7
#define CH3PIN 9

// Relay Banks
#define GUNRELAYPIN PA14
#define LIGHTPIN	PA15

// Various control Pins
#define MODEPIN	PA13

// LCD Control Pins
#define MOSI 	  12
#define SCK	 	  13
#define A0	 	  11
#define LCDRESET  PB7
#define NSS	 	  10

// display modes
#define LCDMODE0 PB2
#define LCDMODE1 PB1
#define LCDMODE2 PB15
#define LCDMODE3 PB14
#define	LCDMODE4 PB13
#define LCDMODE4 PC4


#endif
