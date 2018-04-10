#ifndef I2C_H
#define	I2C_H

#include <xc.h>
#include "main.h"

// datasheet page numbers
// i2c:          383
// master mode:  402, 406
// baud rate:    416
// regs:         422
        
void i2cHardReset();
void i2cInit();
void i2cStartSending(uint8 chipAddr);
void i2cSendByte(uint8 byte);
void i2cStopSending();
void i2cSendTwoBytes(uint8 chipAddr, uint8 byte1, uint8 byte2);
uint8 i2cReadByte(uint8 chipAddr, uint8 regAddr);

#endif	/* I2C_H */


/*
 The following sequence can be bit-banged in order to
ensure that the slave device is properly
reset:

? Start bit
? Clock in nine bits of ?1?
? Start bit
? Stop bit

 */