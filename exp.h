#ifndef EXPANDER_H
#define	EXPANDER_H

#include "main.h"

#define i2cExpAddr 0x27

#define IOCON  0x0B // when bank = 0
#define IODIRA 0x00
#define IODIRB 0x10
#define GPIOA  0x09
#define GPIOB  0x19

void  expInit();
uint8 expReadA();
uint8 expReadB();
void  expWriteB(uint8 byt);
void  expTest();

#endif	/* EXPANDER_H */

