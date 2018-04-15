#ifndef EXPANDER_H
#define	EXPANDER_H

#include "util.h"   

#define swDebounceTime 16  // 2 ms @ 127.2 usecs/tick

#define i2cExpAddr 0x27

// reg addresses in expander chip
#define IODIRA   0x00
#define GPINTENA 0x02  // int enable
#define INTCONA  0x04  // 1: compare to def val, 0: any change
#define INTFA    0x07  // int flags, read-only
#define INTCAPA  0x08  // pin values at time int event occured, read-only
#define GPIOA    0x09
#define IOCON    0x0B  // when bank = 0

#define IODIRB   0x10
#define GPIOB    0x19

enum swIdx {
    swTopLftIdx = 0,
    swBotLftIdx,
    swTopRgtIdx,
    swBotRgtIdx,
    swHomeUpIdx,
    swPwrOffIdx,
    switchesCount
};

extern uint8 swMask[switchesCount];

// switches (port A)
#define swTopLftMask   0x40
#define swBotLftMask   0x20
#define swTopRgtMask   0x10
#define swBotRgtMask   0x08
#define swHomeUpMask   0x02
#define swPwrOffMask   0x01
#define swAllBitsMask  (swTopLftMask|swBotLftMask|swTopRgtMask|  \
                        swBotRgtMask|swHomeUpMask|swPwrOffMask)

void  expInit();
uint8 expReadA();
uint8 expReadB();
void  expWriteB(uint8 byt);
uint8 expSwIntFlags();
uint8 expSwPinValues();
void  expChkSwitches();

#endif	/* EXPANDER_H */

