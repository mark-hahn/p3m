
#include "state.h"
#include "util.h"
#include "exp-panel.h"
#include "lcd.h"
#include "logo.h"
#include "screens.h"

uint8 curState = pwrOffState;

void initState() {
  uint8 swPinValues = expSwPinValues();
  curState = pwrOffState;
}

// [cur state], [switch down=0, up=1], [switch idx]
// {home,pwr, topLft,botLft, topRgt,botRgt}

uint8 nextState[statesCount][2][switchesCount] = {
  // 0: noStateChange
  {{0,0, 0,0, 0,0},                                 
   {0,0, 0,0, 0,0}},
   
   // 1: pwrOffState
  {{0,splashState, 0,0, 0,0},                       
   {0,0, 0,0, 0,0}},
   
   // 2: splashState
  {{mainState,0,                                    
    mainState,mainState,
    mainState, mainState},                          
   {0,pwrOffState, 0,0, 0,0}},
   
   // 3: mainState
  {{menuHelpState,0, 0,0, 0,0},                     
   {0,pwrOffState, 0,0, 0,0}},
  
   // 4: menuHelpState
  {{menuHelp2State,0, 0,0, 0,0},                    
   {0,pwrOffState, 0,0, mainState,menuHelp2State}},
   
   // 5: menuHelp2State
  {{menuHelp3State,0, 0,0, menuHelpState,menuHelp3State},                    
   {0,pwrOffState, 0,0, 0,0}},
   
   // 6: menuHelp3State
  {{menuHelp4State,0, 0,0, menuHelp2State,menuHelp4State},                         
   {0,pwrOffState, 0,0, 0,0}},
   
   // 7: menuHelp4State
  {{mainState,0, 0,0, menuHelp3State,mainState},                         
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

  switch(state) {
    case pwrOffState: lcdOff(); break;
    case splashState: 
      beep();
      logoShowLogo(); 
      delayMs(logoMs);
      state = mainState;
      // fall through
    case mainState: 
      lcdClrAll();
      scrDrawMenu(mainMenu, false, false);
      break;
    case menuHelpState: 
      lcdClrAll();
      scrDrawMenu(menuHelp, true, false);
      break;
    case menuHelp2State: 
      lcdClrAll();
      scrDrawMenu(menuHelp2, true, false);
      break;
    case menuHelp3State: 
      lcdClrAll();
      scrDrawMenu(menuHelp3, true, false);
      break;
    case menuHelp4State: 
      lcdClrAll();
      scrDrawMenu(menuHelp4, true, false);
      break;
    default: return;
  }
  curState = state;
}
