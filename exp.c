
#include <xc.h>

#include "util.h"
#include "exp.h"
#include "i2c.h"
#include "state.h"

uint8 swMask[switchesCount] = {
  swTopLftMask, swBotLftMask, 
  swTopRgtMask, swBotRgtMask, 
  swHomeUpMask, swPwrOffMask
};

uint8 switches;
uint8 swChgCount[8];


void expInit() {
    // expander chip setup
    i2cSendTwoBytes(i2cExpAddr, IOCON,  0x82);       // bank bit = 1, mirror = 0, 
                                                     // not open-drain, active-high
    i2cSendTwoBytes(i2cExpAddr, IODIRA, swAllBitsMask);   // all A (switches) are input
    i2cSendTwoBytes(i2cExpAddr, IODIRB, 0x00);            // B all output
    i2cSendTwoBytes(i2cExpAddr, GPINTENA, swAllBitsMask); // enable switch pin ints
    i2cSendTwoBytes(i2cExpAddr, INTCONA, 0);         // pin ints on any change
    expSwPinValues();  // read to clear all flags
    
    // int pin mcu setup
    TRISC6 = 1;
    IOCIE  = 0;   // no actual interrupts
    IOCCP6 = 1;   // int pin pos edge
    IOCCF6 = 0;   // int flag
    
    switches = expReadA();
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
  return (i2cReadByte(i2cExpAddr, INTCAPA) & swAllBitsMask); 
}

void expChkSwitches() {
  uint8 swPinValues = expReadA();
  for(uint8 i = 0; i < switchesCount; i++) {
    uint8 mask = swMask[i];
    uint8 newval = swPinValues & mask;
    if(newval == (switches & mask)) 
      swChgCount[i] = 0;
    else if(++swChgCount[i] == 5) {
      switches = (switches & ~mask) | newval;
      stateSwitchChange(mask, (newval != 0));
    }
  }
}