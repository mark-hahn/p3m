
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
    mainState,mainState},                          
   {0,pwrOffState, 0,0, 0,0}},
   
   // 3: mainState
  {{menuHelpState,0, mainUpState,mainDnState, 0, mainSelState},                     
   {0,pwrOffState, 0,0, 0,0}},
  
   // 4: menuHelpState
  {{menuHelp2State,0, 0,0, 0,0},                    
   {0,pwrOffState, 0,0, 0,0}},
   
   // 5: menuHelp2State
  {{menuHelp3State,0, 0,0, 0,0},                    
   {0,pwrOffState, 0,0, 0,0}},
   
   // 6: menuHelp3State
  {{mainState,0, 0,0, 0,0},                         
   {0,pwrOffState, 0,0, 0,0}},
   
  // 7: pasteState
  {{mainState,0, 0,0, 0,0},                         
   {0,pwrOffState, 0,0, 0,0}},
   
  // 8: mainUpState
  {{0,0, 0,0, 0,0}, {0,0, 0,0, 0,0}},
  // 8: mainDnState
  {{0,0, 0,0, 0,0}, {0,0, 0,0, 0,0}},
  // 8: mainSelState
  {{0,0, 0,0, 0,0}, {0,0, 0,0, 0,0}}    
};

uint8 selState[menusCount][5] = {
  {pasteState, pickState, inspectState, settingsState}
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
  
chkState:
  switch(state) {
    case pwrOffState: lcdOff(); break;
    case splashState: 
      beep();
      logoShowLogo(); 
      delayMs(logoMs);
      state = mainState;
      goto chkState;
      
    case mainState: 
      lcdClrAll();
      scrDrawMenu(mainMenu, false, false);
      break;
    case mainUpState: scrCursorUp();           return;
    case mainDnState: scrCursorDown(mainMenu); return;
    case mainSelState:
      switch(cursor) {
        case 1: state = selState[mainMenu][cursor-1]; goto chkState;
        default: return;
      }
      
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
      
    case pasteState: 
      lcdClrAll();
      scrDrawMenu(pasteScreen, true, false);
      break;
      
    default: 
      return;
  }
  curState = state;
}
