
#ifndef UTIL_H
#define	UTIL_H

#include <stdbool.h> 

typedef signed char int8;
typedef unsigned char uint8;
typedef int int16;
typedef unsigned int uint16;
typedef short long int24;
typedef unsigned short long uint24;
typedef long int32;
typedef unsigned long uint32;

// by setting this var, DBG=1, you can do a data breakpoint
extern volatile uint8 DBG;
#define BP() __builtin_software_breakpoint()

//#define DBP                                                     \
//    faultLAT = 0;                                               \
//    NOP();  NOP();  NOP();  NOP(); NOP();  NOP();  NOP();       \
//    faultLAT = 1;                                               

#define DBP(macro_PARAM)                                        \
  faultLAT = 0;                                                 \
  for(uint8 macro_mask = 0x80; macro_mask; macro_mask >>= 1) {  \
    faultLAT = 1;                                               \
    if(macro_PARAM & macro_mask) {                              \
      NOP();  NOP();  NOP();  NOP(); NOP();  NOP();  NOP();     \
      NOP();  NOP();  NOP();  NOP(); NOP();  NOP();  NOP();     \
      NOP();  NOP();  NOP();  NOP(); NOP();  NOP();  NOP();     \
      NOP();  NOP();  NOP();  NOP(); NOP();  NOP();  NOP();     \
    }                                                           \
    faultLAT = 0;                                               \
  }                                                             \
  NOP();  NOP();  NOP();  NOP(); NOP();  NOP();  NOP();         \
  NOP();  NOP();  NOP();  NOP(); NOP();  NOP();  NOP();         \
  NOP();  NOP();  NOP();  NOP(); NOP();  NOP();  NOP();         \
  NOP();  NOP();  NOP();  NOP(); NOP();  NOP();  NOP();         \
  NOP();  NOP();  NOP();  NOP(); NOP();  NOP();  NOP();     

#define clkPeriodUs 64
#define beepMs      50

// updated by ints
extern volatile uint16 time;

void utilInit();
void delayMs(uint16 ms);
uint16 getRomWord(uint16 addr);
void beep(uint8 count);

#endif	/* UTIL_H */

