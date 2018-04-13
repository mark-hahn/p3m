
#include <xc.h>

#include "util.h"s
#include "exp.h"
#include "i2c.h"

void expInit() {
    // expander chip setup
    i2cSendTwoBytes(i2cExpAddr, IOCON,  0x82);       // bank bit = 1, mirror = 0, 
                                                     // not open-drain, active-high
    i2cSendTwoBytes(i2cExpAddr, IODIRA, swIntsEn);   // all A (switches) are input
    i2cSendTwoBytes(i2cExpAddr, IODIRB, 0x00);       // B all output
    i2cSendTwoBytes(i2cExpAddr, GPINTENA, swIntsEn); // enable switch pin ints
    i2cSendTwoBytes(i2cExpAddr, INTCONA, 0);         // pin ints on any change
    expSwPinValues();  // read to clear all flags
    
    // int pin mcu setup
    TRISC6 = 1;
    IOCIE  = 0;          // no actual interrupts
    IOCCP6 = swIntsEn;   // int pin pos edge
    IOCCF6 = 0;          // int flag
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

