
#ifndef UTIL_H
#define	UTIL_H

typedef enum {false=0, true} Boolean;
typedef signed char int8;
typedef unsigned char uint8;
typedef int int16;
typedef unsigned int uint16;
typedef short long int24;
typedef unsigned short long uint24;
typedef long int32;
typedef unsigned long uint32;

void dbgInit();
void dbg();

void delayMs(uint16 ms);
uint16 getRomWord(uint16 addr);

#endif	/* UTIL_H */

