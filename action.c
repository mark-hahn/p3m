
#include "action.h"
#include "util.h"
#include "panel.h"
#include "lcd.h"
#include "logo.h"
#include "screens.h"
#include "options.h"
#include "bmotor.h"
#include "smot.h"

// [cur screen], [switch down=0, hold=1, up=2], [switch idx - 2]
// {topLft,botLft, topRgt,botRgt}
const uint8 actionTable[screenCnt][3][rockerCount] = {
  // 0: mainMenu
  {{cursorUpAction,cursorDownAction, escMenuAction,okMenuAction}, 
   {0,0, 0,0},
   {0,0, 0,0}},
  
  // 1: settingsMenu
  {{cursorUpAction,cursorDownAction, escMenuAction,okMenuAction}, 
   {0,0, 0,0},
   {0,0, 0,0}},
  
  // 2: pasteSettingsMenu
  {{cursorUpAction,cursorDownAction, escMenuAction,okMenuAction}, 
   {0,0, 0,0},
   {0,0, 0,0}},
  
  // 8: pasteScreen
  {{0,0, 0,0}, 
   {0,0, 0,0},
   {0,0, 0,0}},
  
  // 9: pickScreen
  {{0,0, 0,0}, 
   {0,0, 0,0},
   {0,0, 0,0}},
  
  // 10: inspectScreen
  {{0,0, 0,0}, 
   {0,0, 0,0},
   {0,0, 0,0}},
};

void doAction(uint8 action) {
chkAction:
  if(action >= scrOfs) {
    curScreen = action - scrOfs;
    if(curScreen < menuCnt) 
      curCursor = defCursByMenu[curScreen];
    lcdClrAll();
    drawScreen(false);
    return;
  }
  switch (action) {
    case pwrOnAction:
      curScreen = logoScrn;
      //  beep(beepMs);  // BREAKS STARTUP ???
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
  }
}

const uint8 screenByMenuAndLine[menuCnt][menuLineCnt] = {
  {pasteScreen,pickScreen,inspectScreen,settingsMenu},
  {pasteSettingsMenu},  
};

void handleHomeSwUpDwn(bool swUp) {
  if(!swUp) {
    switch (curScreen) {
      case menuHelp:  doAction(scrOfs+menuHelp2); break;
      case menuHelp2: doAction(scrOfs+menuHelp3); break;
      case menuHelp3: doAction(scrOfs+mainMenu);  break;
    }
  }
}

void handleHomeSwHold(){
  switch (curScreen) {
    case mainMenu:  doAction(scrOfs+menuHelp);
  }
}

volatile bool   swHoldWaiting[6];
volatile uint16 swDownTimestamp[6];

void handleSwUpDown(uint8 swIdx, bool swUp) {
  if(!swUp) {
    swDownTimestamp[swIdx] = timer();
    swHoldWaiting[swIdx]   = true;
  } else {
    swHoldWaiting[swIdx] = false;
  }
  if(swIdx == swHomeIdx) handleHomeSwUpDwn(swUp);
  else if(swIdx == swPwrIdx) { 
    if(swUp) doAction(pwrOffAction);
    else doAction(pwrOnAction);
  } 
  else {
    doAction(actionTable[curScreen][swUp ? 2 : 0][swIdx-2]);
  }
}

uint16 logoStartTimeStamp;

void timeoutChk(uint8 swIdx) {
  if((curScreen == logoScrn) && 
          (timer() - logoStartTimeStamp) > LOGO_DUR)
    doAction(scrOfs + mainMenu);
  else if(swHoldWaiting[swIdx] && 
          (timer() - swDownTimestamp[swIdx]) > optHoldTime) {
    swHoldWaiting[swIdx] = false;
    if(swIdx == swHomeIdx) 
      handleHomeSwHold();
    else if (swIdx != swPwrIdx)
      doAction(actionTable[curScreen][1][swIdx-2]);
  }
}