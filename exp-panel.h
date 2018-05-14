#ifndef EXPANDER_H
#define	EXPANDER_H

#include "util.h"   

#define swDebounceTime 16  // 2 ms @ 127.2 usecs/tick

#define i2cExpAddr 0x20

// reg addresses in expander chip
#define IODIR     0x00
#define GPINTEN   0x02  // int enable
#define expINTCON 0x04  // 1: compare to def val, 0: any change
#define INTF      0x07  // int flags, read-only
#define INTCAP    0x08  // pin values at time int event occured, read-only
#define GPIO      0x09
#define IOCON     0x0B  // when bank = 0

enum swIdx {
    swHomeUpIdx = 0,
    swPwrOffIdx,
    swBotRgtIdx,
    swBotLftIdx,
    swTopRgtIdx,
    swTopLftIdx,
    switchesCount
};

extern uint8 swMask[switchesCount];

// switches (port A)
#define swHomeUpMask   0x01
#define swPwrOffMask   0x02
#define swBotRgtMask   0x04
#define swBotLftMask   0x08
#define swTopRgtMask   0x10
#define swTopLftMask   0x20
#define buzzMask       0x80

#define swAllSwMask  (swTopLftMask|swBotLftMask|swTopRgtMask|  \
                        swBotRgtMask|swHomeUpMask|swPwrOffMask)

void  expPanelInit();
uint8 expReadA();
void  expWriteA(uint8 data);
uint8 expSwIntFlags();
uint8 expSwPinValues();
void  expChkSwitches();

#endif	/* EXPANDER_H */

