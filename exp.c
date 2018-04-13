
#include <xc.h>

#include "util.h"
#include "exp.h"
#include "i2c.h"

void expInit() {
    i2cSendTwoBytes(i2cExpAddr, IOCON,  0x80);       // bank bit = 1
    i2cSendTwoBytes(i2cExpAddr, IODIRA, swAll);      // all switches are input
    i2cSendTwoBytes(i2cExpAddr, IODIRB, 0x00);       // B all output
    i2cSendTwoBytes(i2cExpAddr, GPINTENA, swIntsEn); // enable sw pin ints
    i2cSendTwoBytes(i2cExpAddr, INTCONA, 0);         // pin ints on any change
    
    // int pin mcu setup
    intPinTRIS = 1;
    intPinIOCN = 1; // int on neg edge
    intPinIOCF = 0;
}

uint8 expReadA() {
    return i2cReadByte(i2cExpAddr, GPIOA);
}

uint8 expReadB() {
    return i2cReadByte(i2cExpAddr, GPIOB);
}

void expWriteB(uint8 byt) {
    i2cSendTwoBytes(i2cExpAddr, GPIOB, byt);
}

uint8 expSwIntFlags() {
  return i2cReadByte(i2cExpAddr, INTFA);
}

uint8 expSwPinValues() {
  return i2cReadByte(i2cExpAddr, INTCAPA); 
}

void expTest() {
    i2cSendTwoBytes(i2cExpAddr, IODIRA, 0x00);  // all outputs
    while(1) {
        i2cSendTwoBytes(i2cExpAddr, GPIOA, 0x00);  // pins = 0
        i2cSendTwoBytes(i2cExpAddr, GPIOA, 0xff);  // pins = 1
        int x = i2cReadByte(i2cExpAddr, 0x05);  // IOCON in bank=1 mode
    }
}
