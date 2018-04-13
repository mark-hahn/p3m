#ifndef EXPANDER_H
#define	EXPANDER_H

#include "util.h"

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

// switches (port A)
#define swTopLft   0x40
#define swBotLft   0x20
#define swTopRgt   0x10
#define swBotRgt   0x08
#define swHomeUp   0x02
#define swPwrOff   0x01
#define swIntsEn   (swTopLft|swBotLft|swTopRgt|swBotRgt|swHomeUp|swPwrOff)

void  expInit();
uint8 expReadA();
uint8 expReadB();
void  expWriteB(uint8 byt);
uint8 expSwIntFlags();
uint8 expSwPinValues();

#endif	/* EXPANDER_H */

