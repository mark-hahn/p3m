
#include "action.h"
#include "util.h"
#include "exp-panel.h"
#include "lcd.h"
#include "logo.h"
#include "screens.h"
#include "options.h"
#include "bmotor.h"
#include "smot.h"

// [cur state], [switch down=0, hold=1, up=2], [switch idx]
// {home,pwr, topLft,botLft, topRgt,botRgt}
const uint8 actionTable[screenCnt][3][switchesCount] = {
  // 0: mainMenu
  {{scrOfs+menuHelp,0, menuUpAction,menuDownAction, escAtion,okAction}, 
   {0,0, 0,0, 0,0},
   {0,pwrOffAction, 0,0, 0,0}},
  
  // 1: settingsMenu
  {{scrOfs+mainMenu,0, menuUpAction,menuDownAction, escAtion,okAction}, 
   {0,0, 0,0, 0,0},
   {0,pwrOffAction, 0,0, 0,0}},
  
  // 2: pasteSettingsMenu
  {{0,0, 0,0, 0,0}, 
   {0,0, 0,0, 0,0},
   {0,pwrOffAction, 0,0, 0,0}},
  
  // 3: pwrOffScrn
  {{0,scrOfs+mainMenu, 0,0, 0,0}, 
   {0,0, 0,0, 0,0},
   {0,0, 0,0, 0,0}},
  
  // 4: menuHelp
  {{scrOfs+menuHelp2,0, 0,0, 0,0}, 
   {0,0, 0,0, 0,0},
   {0,pwrOffAction, 0,0, 0,0}},
  
  // 5: menuHelp2
  {{scrOfs+menuHelp3,0, 0,0, 0,0}, 
   {0,0, 0,0, 0,0},
   {0,pwrOffAction, 0,0, 0,0}},
  
  // 6: menuHelp3
  {{scrOfs+mainMenu,0, 0,0, 0,0}, 
   {0,0, 0,0, 0,0},
   {0,pwrOffAction, 0,0, 0,0}},
  
  // 7: pasteScreen
  {{0,0, 0,0, 0,0}, 
   {0,0, 0,0, 0,0},
   {0,pwrOffAction, 0,0, 0,0}},
  
  // 8: pickScreen
  {{0,0, 0,0, 0,0}, 
   {0,0, 0,0, 0,0},
   {0,pwrOffAction, 0,0, 0,0}},
  
  // 9: inspectScreen
  {{0,0, 0,0, 0,0}, 
   {0,0, 0,0, 0,0},
   {0,pwrOffAction, 0,0, 0,0}},
};
  
//   // 3: mainState
//  {{menuHelpState,0, upAction,downAction, 0,selAction},                     
//   {0,pwrOffState, 0,0, 0,0}},
//  
//   // 4: menuHelpState
//  {{menuHelp2State,0, 0,0, 0,0},                    
//   {0,pwrOffState, 0,0, 0,0}},
//   
//   // 5: menuHelp2State
//  {{menuHelp3State,0, 0,0, 0,0},                    
//   {0,pwrOffState, 0,0, 0,0}},
//   
//   // 6: menuHelp3State
//  {{mainState,0, 0,0, 0,0},                         
//   {0,pwrOffState, 0,0, 0,0}},
//   
//  // 7: pasteState
//  {{mainState,0, 0,0, 0,0},                         
//   {0,pwrOffState, 0,0, 0,0}},
//   
//  // 8: pickState
//  {{mainState,0, 0,0, 0,0},                         
//   {0,pwrOffState, 0,0, 0,0}},
//  
//  // 9: inspectState
//  {{mainState,0, 0,0, upAction,downAction},                         
//   {0,pwrOffState, 0,0,  upOffAction,downOffAction}},
//   
//  // 10: settingsState
//  {{mainState,0, upAction,downAction, mainState,selAction},                     
//   {0,pwrOffState, 0,0, 0,0}},
//
//   // 11: pasteSettingState
//   {{mainState,0, upAction,downAction, settingsState,selAction},               
//   {0,pwrOffState, 0,0, 0,0}},
//   
//  // 12: rotateSettingState
//  {{mainState,0, 0,0, 0,0},                         
//   {0,pwrOffState, 0,0, 0,0}},
//   
//  // 13: pinchSettingState
//  {{mainState,0, 0,0, 0,0},                         
//   {0,pwrOffState, 0,0, 0,0}},
//  
//  // 14: extrudeDistState
//   {{mainState,0, upOptAction,downOptAction, escAction,selOptAction},                     
//   {0,pwrOffState, 0,0, 0,0}},  
//  
//  // 15: extrudeRateState
//   {{mainState,0, upOptAction,downOptAction, escAction,selOptAction},                     
//   {0,pwrOffState, 0,0, 0,0}},    
//};

void doAction(uint8 action) {
  if(action >= scrOfs) {
    curScreen = action - scrOfs;
    lcdClrAll();
    drawScreen(curScreen, true, false);
    return;
  }

  switch (action) {
    case pwrOffAction:
      lcdOff(); 
      bmotAllPwrOff();
      smotAllPwrOff();
      curScreen = pwrOffScrn;
      return;
      
    case menuUpAction:   
      
      break;
    case menuDownAction:
      
      break;
    case settingsUpAction:
      
      break;
    case settingsDownAction:
      
      break;
    case escAtion:
      
      break;
    case okAction:
      
      break;
  }
}

const uint8 screenByMenuAndLine[menuCnt][menuLineCnt] = {
  {pasteScreen,pickScreen,inspectScreen,settingsMenu},
  {pasteSettingsMenu},  
};

volatile bool   swHoldWaiting[6];
volatile uint16 swDownTimestamp[6];

void handleSwHoldStart(uint8 swIdx) {
  doAction(actionTable[curScreen][1][swIdx]);
}

void handleSwUpDown(uint8 switchMask, bool swUp) {
  for(uint8 swIdx=0; swIdx < switchesCount; swIdx++) {
    if(switchMask == swMask[swIdx]) {
      if(!swUp) {
        swDownTimestamp[swIdx] = timer();
        swHoldWaiting[swIdx]   = true;
      }
//      if(curScreen == splashScreenIdx);
      doAction(actionTable[curScreen][swUp ? 2 : 0][swIdx]);
      break;
    }
  }
}


/*
 
uint8 actionState[menusCount][5] = {
  {pasteState, pickState, inspectState, settingsState},       // mainMenu
  {pasteSettingState, rotateSettingState, pinchSettingState}, // settingsMenu
  {extrudeDistState, 0, extrudeRateState},                    // pasteSettingState
};

void stateEnter(uint8 state) {
chkState:
  switch(state) {
    case upAction:   
      switch(curScreen) {
        case inspectScreen: 
          startSmot(pasteMotor, -1, 200, 65535);
          break;
        default: 
          scrCursorUp(false); 
          break;
      }
      return;
    case downAction: 
      switch(curScreen) {
        case inspectScreen: 
          startSmot(pasteMotor, +1, 200, 65535);
          break;
        default: 
          scrCursorDown(false); 
          break;
      }
      return;
    case upOffAction:
    case downOffAction:
      stopSmot(pasteMotor);
      return;

    case selAction:
      state = actionState[curScreen][curCursor-1];
      goto chkState;
      
    case upOptAction:   
      optValUp(editingOption);
      scrRedrawMenu();
      return;
    case downOptAction: 
      optValDown(editingOption);
      scrRedrawMenu();      
      return;
    case selOptAction: 
      saveOptions(); 
      // fall through
    case escAction: 
      loadOptions();
      editingOption = 0;
      scrCursorUp(true); 
      switch(curScreen) {
        case pasteSettingsMenu: state = pasteSettingState; break;
      }
      goto chkState;
      
    case pwrOffState: 
      lcdOff(); 
      bmotAllPwrOff();
      smotAllPwrOff();
      break;
    case splashState: 
      initCursor();
      beep(1);
//      logoShowLogo(); 
//      delayMs(logoMs);
      state = mainState;
      goto chkState;
      
    case mainState: 
      initCursor();
      lcdClrAll();
      scrDrawMenu(mainMenu, false, false);
      break;
    
    case settingsState: 
      initCursor();
      lcdClrAll();
      scrDrawMenu(settingsMenu, false, false);
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
      
    case pasteState: 
      lcdClrAll();
      scrDrawMenu(pasteScreen, true, false);
      break;
      
    case pickState: 
      lcdClrAll();
      scrDrawMenu(pickScreen, true, false);
      break;
      
    case inspectState: 
      lcdClrAll();
      scrDrawMenu(inspectScreen, true, false);
      break;
      
    case pasteSettingState:
      lcdClrAll();
      scrDrawMenu(pasteSettingsMenu, false, false);
      break;
    case extrudeDistState: openOptionField(pasteClickOption); break;
    case extrudeRateState: openOptionField(pasteHoldOption);  break;

    default: 
      return;
  }
  curState = state;
}
*/