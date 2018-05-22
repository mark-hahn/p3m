
#include "state.h"
#include "util.h"
#include "exp-panel.h"
#include "lcd.h"
#include "logo.h"
#include "screens.h"
#include "options.h"

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
  {{menuHelpState,0, upAction,downAction, 0,selAction},                     
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
   
  // 8: pickState
  {{mainState,0, 0,0, 0,0},                         
   {0,pwrOffState, 0,0, 0,0}},
  
  // 9: inspectState
  {{mainState,0, 0,0, 0,0},                         
   {0,pwrOffState, 0,0, 0,0}},
   
  // 10: settingsState
  {{mainState,0, upAction,downAction, mainState,selAction},                     
   {0,pwrOffState, 0,0, 0,0}},

   // 11: pasteSettingState
   {{mainState,0, upAction,downAction, settingsState,selAction},               
   {0,pwrOffState, 0,0, 0,0}},
   
  // 12: rotateSettingState
  {{mainState,0, 0,0, 0,0},                         
   {0,pwrOffState, 0,0, 0,0}},
   
  // 13: pinchSettingState
  {{mainState,0, 0,0, 0,0},                         
   {0,pwrOffState, 0,0, 0,0}},
  
  // 14: extrudeDistState
   {{mainState,0, upOptAction,downOptAction, escAction,selOptAction},                     
   {0,pwrOffState, 0,0, 0,0}},  
  
  // 15: extrudeRateState
   {{mainState,0, upOptAction,downOptAction, escAction,selOptAction},                     
   {0,pwrOffState, 0,0, 0,0}},    
};

void stateSwitchChange(uint8 switchMask, bool swUp) {
  for(uint8 swIdx=0; swIdx < switchesCount; swIdx++) {
    if(switchMask == swMask[swIdx]) {
      stateEnter(nextState[curState][swUp][swIdx]);
      break;
    }
  }
}

uint8 actionState[menusCount][5] = {
  {pasteState, pickState, inspectState, settingsState},       // mainMenu
  {pasteSettingState, rotateSettingState, pinchSettingState}, // settingsMenu
  {extrudeDistState, 0, extrudeRateState},                    // pasteSettingState
};

void stateEnter(uint8 state) {
chkState:
  switch(state) {
    case upAction:   scrCursorUp(false);   return;
    case downAction: scrCursorDown(false); return;
    case selAction:
      state = actionState[curMenu][curCursor-1];
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
      switch(curMenu) {
        case pasteSettingsMenu: state = pasteSettingState; break;
      }
      goto chkState;
      
    case pwrOffState: 
      lcdOff(); 
      break;
    case splashState: 
      initCursor();
//      beep();
      logoShowLogo(); 
      delayMs(logoMs);
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
