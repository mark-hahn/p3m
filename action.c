
#include "action.h"
#include "util.h"
#include "panel.h"
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
  {{scrOfs+menuHelp,0, cursorUpAction,cursorDownAction, escMenuAction,okMenuAction}, 
   {0,0, 0,0, 0,0},
   {0,pwrOffAction, 0,0, 0,0}},
  
  // 1: settingsMenu
  {{scrOfs+mainMenu,0, cursorUpAction,cursorDownAction, escMenuAction,okMenuAction}, 
   {0,0, 0,0, 0,0},
   {0,pwrOffAction, 0,0, 0,0}},
  
  // 2: pasteSettingsMenu
  {{scrOfs+mainMenu,0, cursorUpAction,cursorDownAction, escMenuAction,okMenuAction}, 
   {0,0, 0,0, 0,0},
   {0,pwrOffAction, 0,0, 0,0}},
  
  // 3: pwrOffScrn
  {{0,scrOfs+logoScrn, 0,0, 0,0}, 
   {0,0, 0,0, 0,0},
   {0,0, 0,0, 0,0}},
  
  // 4: logoScrn
  {{scrOfs+mainMenu,0, 0,0, 0,0}, 
   {0,0, 0,0, 0,0},
   {0,pwrOffAction, 0,0, 0,0}},
  
  // 5: menuHelp
  {{scrOfs+menuHelp2,0, 0,0, 0,0}, 
   {0,0, 0,0, 0,0},
   {0,pwrOffAction, 0,0, 0,0}},
  
  // 6: menuHelp2
  {{scrOfs+menuHelp3,0, 0,0, 0,0}, 
   {0,0, 0,0, 0,0},
   {0,pwrOffAction, 0,0, 0,0}},
  
  // 7: menuHelp3
  {{scrOfs+mainMenu,0, 0,0, 0,0}, 
   {0,0, 0,0, 0,0},
   {0,pwrOffAction, 0,0, 0,0}},
  
  // 8: pasteScreen
  {{scrOfs+mainMenu,0, 0,0, 0,0}, 
   {0,0, 0,0, 0,0},
   {0,pwrOffAction, 0,0, 0,0}},
  
  // 9: pickScreen
  {{scrOfs+mainMenu,0, 0,0, 0,0}, 
   {0,0, 0,0, 0,0},
   {0,pwrOffAction, 0,0, 0,0}},
  
  // 10: inspectScreen
  {{scrOfs+mainMenu,0, 0,0, 0,0}, 
   {0,0, 0,0, 0,0},
   {0,pwrOffAction, 0,0, 0,0}},
};
  
void doAction(uint8 action) {
chkAction:
  if(action >= scrOfs) {
    curScreen = action - scrOfs;
    if(curScreen < menuCnt) 
      lastCursor = curCursor = cursorByMenu[curScreen];
    lcdClrAll();
    drawScreen(false);
    return;
  }
  switch (action) {
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

volatile bool   swHoldWaiting[6];
volatile uint16 swDownTimestamp[6];

void handleSwUpDown(uint8 switchMask, bool swUp) {
  for(uint8 swIdx=0; swIdx < switchesCount; swIdx++) {
    if(switchMask == swMask[swIdx]) {
      if(!swUp) {
        swDownTimestamp[swIdx] = timer();
        swHoldWaiting[swIdx]   = true;
      } else {
        swHoldWaiting[swIdx] = false;
      }
      doAction(actionTable[curScreen][swUp ? 2 : 0][swIdx]);
      break;
    }
  }
}

uint16 logoStartTimeStamp;

void actionChk(uint8 swIdx) {
  if(swHoldWaiting[swIdx] && 
        (timer() - swDownTimestamp[swIdx]) > optHoldTime) {
    swHoldWaiting[swIdx] = false;
    doAction(actionTable[curScreen][1][swIdx]);
  }
  if((curScreen == logoScrn) && (timer() - logoStartTimeStamp) > LOGO_DUR)
    doAction(scrOfs + mainMenu);
}

void poweredUp() {
  curScreen = logoScrn;
//  beep(beepMs);  // BREAKS STARTUP ???
  initCursor();
  logoStartTimeStamp = timer();
  logoShowLogo();
}