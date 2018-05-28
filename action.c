/*
 TODO: home camera should cancel home hold
 */

#include "action.h"
#include "util.h"
#include "panel.h"
#include "lcd.h"
#include "logo.h"
#include "screens.h"
#include "options.h"
#include "bmotor.h"
#include "smot.h"
#include "lights.h"

uint16 logoStartTimeStamp;
int8 focusDir = 1;
uint8 glblockerSwIdx;

void doAction(uint8 action) {
chkAction:
  if(action >= scrOfs) {
    uint8 scrnIdx = action - scrOfs;
    if(scrnIdx == curScreen) return;
    curScreen = scrnIdx;
    if(curScreen < menuCnt) 
      curCursor = defCursByMenu[curScreen];
    lcdClrAll();
    drawScreen(false);
    return;
  }
  switch (action) {
    case pwrOnAction:
      curScreen = logoScrn;
      beep(1);
      initCursor();
      logoStartTimeStamp = timer();
      logoShowLogo();
      return;

    case pwrOffAction:
      lcdOff(); 
      bmotAllPwrOff();
      smotAllPwrOff();
      curScreen = pwrOffScrn;
      return;
      
    case cursorUpAction:   scrCursorUp(false);   return;
    case cursorDownAction: scrCursorDown(false); return;
    case escMenuAction: 
      action = scrOfs + parentMenu[curScreen]; 
      goto chkAction;
    case okMenuAction:
      action = scrOfs + menuSelScreen[curScreen][curCursor-1];
      goto chkAction;
      
    case lightsAction:  chgLights(); break;
    
    case focusAction:   
      startSmot(focusMotor, focusDir, 100, 65535);
      focusDir = -focusDir;
      actionOnSwUp[glblockerSwIdx] = focusEndAction;
      break;
    case focusEndAction: stopSmot(focusMotor); break;
      
    case zoomInAction:   
      startBmot(zoomMotor, 1, true, 500, 65535);
      actionOnSwUp[glblockerSwIdx] = zoomEndAction;
      break;
    case zoomOutAction:   
      startBmot(zoomMotor, 1, false, 500, 65535);
      actionOnSwUp[glblockerSwIdx] = zoomEndAction;
      break;
    case zoomEndAction: stopBmot(zoomMotor); break;
    
    case syringeInAction:  beep(1); break;
    case syringeOutAction: beep(1); break;
    case extrudeAction:    beep(1); break;
    case retractAction:    beep(1); break;
  }
}

void doActionSw(uint8 action, uint8 swIdx) {
  glblockerSwIdx = swIdx - 2;
  doAction(action);
}

const uint8 screenByMenuAndLine[menuCnt][menuLineCnt] = {
  {pasteScreen,pickScreen,inspectScreen,settingsMenu},
  {pasteSettingsMenu},  
};

bool  cameraMode;
bool  turboMode;
uint8 actionOnTurboStart;
uint8 actionOnTurboEnd;
uint8 actionOnHoldStart;
uint8 actionOnSwUp[rockerCount];

void handleHomeSwUpDwn(bool swUp) {
  if(!swUp) {  // switch down
    if(actionOnTurboStart) {
      turboMode = true;
      doAction(actionOnTurboStart); 
      return;
    }
  } else { // switch up
    if(turboMode) {
      turboMode = false;
      if(actionOnTurboEnd) doAction(actionOnTurboEnd);
    }
    else if(!cameraMode) {
      switch (curScreen) {
        case mainMenu:  doAction(scrOfs+menuHelp);  break;
        case menuHelp:  doAction(scrOfs+menuHelp2); break;
        case menuHelp2: doAction(scrOfs+menuHelp3); break;
        default: doAction(scrOfs+mainMenu);
      }
    }
    cameraMode = turboMode = false;
  }
}

#define cameraAction 200
#define menuAction   201

uint8 actionTable[5][5] = {
  {cameraAction,   lightsAction,focusAction, zoomInAction,zoomOutAction},
  {menuAction,   cursorUpAction,cursorDownAction, escMenuAction,okMenuAction},
  {pasteScreen, syringeInAction,syringeOutAction, extrudeAction,retractAction},
  {pickScreen,    0,0,0,0},
  {inspectScreen, 0,0,0,0},
};

void doRockerAction(uint8 actMode, uint8 swIdx) {
  for(int tblIdx=0; tblIdx < 5; tblIdx++) {
    if(actionTable[tblIdx][0] == actMode) {
       doActionSw(actionTable[tblIdx][swIdx-2+1], swIdx);  
       return;
    }
  }
}

volatile bool   swHoldWaiting[6];
volatile uint16 swDownTimestamp[6];

void handleSwUpDown(uint8 swIdx, bool swUp) {
  if(curScreen == pwrOffScrn && swIdx != swPwrIdx) return;
  
  if(!swUp) {                   // switch down
    swDownTimestamp[swIdx] = timer();
    swHoldWaiting[swIdx]   = true;
  } else {                      // switch up
    swHoldWaiting[swIdx] = false;
    if(actionOnSwUp[swIdx-2]) {
      doAction(actionOnSwUp[swIdx-2]);
      actionOnSwUp[swIdx-2] = 0;
    }
  }
  
  if(swIdx == swHomeIdx)        // home switch
    handleHomeSwUpDwn(swUp);
  
  else if(swIdx == swPwrIdx) {  // power switch
    if(swUp) doAction(pwrOffAction);
    else     doAction(pwrOnAction);
  } 
  else {                        // rocker switch
    if(swUp) {
      if(turboMode) {
        turboMode = false;
        if(actionOnTurboEnd) doAction(actionOnTurboEnd);
      }
      return;
    }
    if(cameraMode = ((curSwitches & swHomeMask) == 0)) {
      doRockerAction(cameraAction, swIdx);
      return;
    } 
    if(curScreen < menuCnt) {  // menu
      doRockerAction(menuAction, swIdx); 
      return;
    }
    else { // paste, pick, or inspect screen
      doRockerAction(curScreen, swIdx); 
      return;
    }
  }
}

void timeoutChk(uint8 swIdx) {
  if((curScreen == logoScrn) && 
          (timer() - logoStartTimeStamp) > LOGO_DUR)
    doAction(scrOfs + mainMenu);
  
  else if(swHoldWaiting[swIdx] && 
          (timer() - swDownTimestamp[swIdx]) > optHoldTime) {
    swHoldWaiting[swIdx] = false;
//    if(swIdx == swHomeIdx) {
//      if (curScreen == mainMenu) doAction(scrOfs+menuHelp);
//    } 
    if(actionOnHoldStart) doAction(actionOnHoldStart);
  }
}