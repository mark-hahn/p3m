
#include <xc.h>
#include "util.h"
#include "exp-panel.h"
#include "bmotor.h"

void bmotorInit() {
  resetLAT = 0;  // start with reset low (resetted)
  
  // all big motor pins are outputs
  TRISB = TRISB & ~bmotPinsB;
  TRISC = TRISC & ~bmotPinsC;

//  faultTRIS = 0;
}

struct bmotStateStruct bmotState[3];

void setBmotInfo(uint8 motorIdx, uint8 ustep, bool fwdDir, uint16 pps) {
  bmotState[motorIdx].ustep   = ustep << 3;
  bmotState[motorIdx].fwdDir  = fwdDir;
  bmotState[motorIdx].rateInc = 2000 / pps;  // max pps = 2 khz
}

void startBmot(uint8 motorIdx, uint16 count) {
  DBG = 1;
  // count must be > 0,  65535 == forever
  bmotState[motorIdx].count = count;
  resetLAT = 1; // not resetting
}

void stopBmot(uint8 motorIdx) {
   bmotState[motorIdx].count = 0;
   if(bmotState[0].count + bmotState[1].count + bmotState[2].count == 0)
     resetLAT = 0; // power down all big motors
}

uint8 bmotStepCtr[3] = 0;
uint8 delay;

// big motor interrupt routine
void bmotInt(uint8 motorIdx) {
  struct bmotStateStruct *pState = &bmotState[motorIdx];
  uint8                  *pCtr   = &bmotStepCtr[motorIdx];
  
  if (pState->count && (++*pCtr == pState->rateInc)) {
    *pCtr = 0;
    if(pState->count < 65535) pState->count--;
    LATB = (LATB & 0xc6) | pState->ustep | pState->fwdDir;
    delay = 2;
    switch(motorIdx) {
      case 0: LATC5 = 0;  while(--delay > 0) NOP(); LATC5 = 1;  break;
      case 1: LATC6 = 0;  while(--delay > 0) NOP(); LATC6 = 1;  break;
      case 2: LATC7 = 0;  while(--delay > 0) NOP(); LATC7 = 1;  break;
    }
  }
}