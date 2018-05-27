
#include <xc.h>

#include "util.h"
#include "panel.h"
#include "i2c.h"
#include "action.h"

uint8 swMask[switchesCount] = {
  swHomeMask,   swPwrMask, 
  swTopLftMask, swBotLftMask, 
  swTopRgtMask, swBotRgtMask
};

uint8 switches;
uint8 debounceCount[switchesCount];


void panelInit() {
    // expander chip setup
    i2cSendTwoBytes(i2cExpAddr, IOCON,  0x22); // not seq op, no slew, not open-drain, active-high
    i2cSendTwoBytes(i2cExpAddr, GPIO, 0xff);           // start buzz off, high
    i2cSendTwoBytes(i2cExpAddr, IODIR, swAllSwMask);   // all switches are input, buzz is output
    i2cSendTwoBytes(i2cExpAddr, GPINTEN, swAllSwMask); // enable switch pin ints
    i2cSendTwoBytes(i2cExpAddr, expINTCON, 0);         // pin ints on any change
    
    switches = swAllSwMask;
}

uint8 panelReadA() {
    return i2cReadByte(i2cExpAddr, GPIO);
}

void panelWriteA(uint8 data) {
    i2cSendTwoBytes(i2cExpAddr, GPIO, data);
}

uint8 panelSwPinValues() {
  return (i2cReadByte(i2cExpAddr, INTCAP) & swAllSwMask); 
}

void panelChkSwitches() {
  uint8 swPinValues = panelReadA();
  for(uint8 i = 0; i < switchesCount; i++) {
    uint8 mask = swMask[i];
    uint8 newval = swPinValues & mask;
    // debounce
    if(newval == (switches & mask)) 
      debounceCount[i] = 0;
    else if(++debounceCount[i] == 5) {
      switches = (switches & ~mask) | newval;
      handleSwUpDown(mask, (newval != 0));
    }
  }
  if((curScreen == pwrOffScrn) && (swPinValues & swPwrMask) == 0)
    poweredUp();
}