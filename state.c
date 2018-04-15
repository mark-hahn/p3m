
#include "state.h"
#include "exp.h"
#include "lcd.h"
#include "logo.h"
#include "screens.h"

uint8 curState = pwrOffState;

void initState() {
  stateEnter((expSwPinValues() & swPwrOffMask) ? pwrOffState : splashState);
}

// [cur state], [switch down=0, up=1], [switch idx]
// switch idx = swTopLft, swBotLft, 
//              swTopRgt, swBotRgt 
//              swHomeUp, swPwrOff 
uint8 nextState[statesCount][2][switchesCount] = {
  {{0,0,0,0,0,0},                                             // noStateChange
   {0,0,0,0,0,0}},
  {{0,0,0,0,0, splashState},                                  // pwrOffState
   {0,0,0,0,0,0}},
  {{mainState,mainState,mainState,mainState, mainState, 0},   // splashState
   {0,0,0,0,0,pwrOffState}},
  {{0,0,0,0,0,0},                                             // mainState
   {0,0,0,0,0,pwrOffState}}
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
  if(curState == pwrOffState && state != pwrOffState) {
    lcdOn();
    state = splashState;
  }
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
