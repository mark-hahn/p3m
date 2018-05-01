
#include <xc.h>

#include "util.h"
#include "exp-panel.h"
#include "i2c.h"
#include "state.h"

uint8 swMask[switchesCount] = {
  swTopLftMask, swBotLftMask, 
  swTopRgtMask, swBotRgtMask, 
  swHomeUpMask, swPwrOffMask
};

uint8 switches;
uint8 swChgCount[8];


void expPanelInit() {
    // expander chip setup
    i2cSendTwoBytes(i2cExpAddr, IOCON,  0x22); // not seq op, no slew, not open-drain, active-high
    i2cSendTwoBytes(i2cExpAddr, IODIR, swAllBitsMask);   // all A (switches) are input
    i2cSendTwoBytes(i2cExpAddr, GPINTEN, swAllBitsMask); // enable switch pin ints
    i2cSendTwoBytes(i2cExpAddr, expINTCON, 0);         // pin ints on any change
    expSwPinValues();  // read to clear all flags
    
    // int pin mcu setup
    TRISC6 = 1;
    IOCIE  = 0;   // no actual interrupts
    IOCCP6 = 1;   // int pin pos edge
    IOCCF6 = 0;   // int flag
    
    switches = expReadA();
}

uint8 expReadA() {
    return i2cReadByte(i2cExpAddr, GPIO);
}

uint8 expSwIntFlags() {
  return i2cReadByte(i2cExpAddr, INTF);
}

uint8 expSwPinValues() {
  return (i2cReadByte(i2cExpAddr, INTCAP) & swAllBitsMask); 
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
      dbgToggle();
    }
  }
}