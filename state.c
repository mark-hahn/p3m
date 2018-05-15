
#include "state.h"
#include "exp-panel.h"
#include "lcd.h"
#include "logo.h"
#include "screens.h"

uint8 curState = pwrOffState;

void initState() {
  uint8 swPinValues = expSwPinValues();
  stateEnter((swPinValues & swPwrMask) ? pwrOffState : splashState);
}

// [cur state], [switch down=0, up=1], [switch idx]
// {home,pwr, topLft,botLft, topRgt,botRgt}

uint8 nextState[statesCount][2][switchesCount] = {
  {{0,0, 0,0, 0,0},                                 // 0: noStateChange
   {0,0, 0,0, 0,0}},
   
  {{0,splashState, 0,0, 0,0},                       // 1: pwrOffState
   {0,0, 0,0, 0,0}},
   
  {{mainState,0,                                    // 2: splashState
    mainState,mainState,
    mainState, mainState},                          
   {0,pwrOffState, 0,0, 0,0}},
   
  {{0,0, 0,0, 0,0},                                 // 3: mainState
   {0,pwrOffState, 0,0, 0,0}}
};

void stateSwitchChange(uint8 switchMask, bool swUp) {
  for(uint8 swIdx=0; swIdx < switchesCount; swIdx++) {
    if(switchMask == swMask[swIdx]) {
      stateEnter(nextState[curState][swUp][swIdx]);
      break;
    }
  }
}

void stateEnter(uint8 state) {
  if(!state) return;
  if(curState == pwrOffState && state != pwrOffState)  
    lcdOn();

  switch(state) {
    case pwrOffState: lcdOff(); break;
    case splashState: logoShowLogo(); break;
    case mainState: 
      lcdClrAll();
      scrDrawMenu(mainMenu, false);
      break;
    default: return;
  }
  curState = state;
}
