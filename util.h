
#ifndef UTIL_H
#define	UTIL_H

#include <stdbool.h> 

//#define FAULT_DEBUG
//#define LCD_DEBUG

typedef signed char int8;
typedef unsigned char uint8;
typedef int int16;
typedef unsigned int uint16;
typedef short long int24;
typedef unsigned short long uint24;
typedef long int32;
typedef unsigned long uint32;

#define clkPeriodUs 64
#define beepMs      50

void utilInit();
void dbg();
void dbgToggle();
uint16 timer();
void delay128Usecs(uint16 ticks);
void delayMs(uint16 ms);
uint16 getRomWord(uint16 addr);
void beep();

#endif	/* UTIL_H */

