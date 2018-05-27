
#include "screens.h"
#include "lcd.h"
#include "font708.h"
#include "font813.h"
#include "strings.h"
#include "options.h"
#include "panel.h"

uint8 menuLines[screenCnt][6] = {
   {mainMenuStr, 
    pasteStr,
    pickStr,
    inspectStr,
    settingsStr,
    menuHelpStr,
   },
    
   {settingsMenuStr,
    pasteStr,
    sm1Str,
   },
   
   {pasteSettingsMenuStr,
    ps1Str,
    pasteClickOption,
    ps2Str,
    pasteHoldOption,
   },
   
   {helpMenuStr,
    hm1Str,
    hm2Str,
    hm3Str,
    hm4Str,
    hm5Str,
   },
    
   {helpMenu2Str, 
    hm6Str,
    hm7Str,
    hm8Str,
    hm9Str,
    hm5Str,
   },
    
   {helpMenu2Str, 
    hm10Str,
    hm11Str,
    hm12Str,
    hm13Str,
    hm5Str,
    },
    
   {pasteScreenStr, 
    paste1Str,
    paste2Str,
    lightsStr,
    focusStr,
    zoomStr,
    },
    
   {pickScreenStr, 
    pick1Str,
    pick2Str,
    lightsStr,
    focusStr,
    zoomStr,
    },
    
   {inspectScreenStr, 
    inspect1Str,
    inspect2Str,
    lightsStr,
    focusStr,
    inspect3Str,
    },
};

uint8 curCursor, lastCursor;
uint8 curScreen;

void initCursor() {
  curCursor = 1;
  lastCursor = 1;
  for(int i=0; i<menuCnt; i++)
    defCursByMenu[i] = 1;
}
void initScreens() {
  initCursor();
  curScreen = pwrOffScrn;
}

char *menuLine(uint8 line){
  if(menuLines[curScreen][line] < firstOptionCode)
    return romStr(menuLines[curScreen][line]);
  else
    return optionStr(menuLines[curScreen][line]);
}

void drawScreen(bool cursorOnly) {
  if(!cursorOnly) {
    lcdClrPage(0);
    lcdClrPage(1);
    font813WriteStr(0,  0, 0, menuLine(0));
    font813WriteStr(1, -8, 0, menuLine(0));
  }
  if(curScreen < menuCnt) {
    if(!cursorOnly || curCursor == 1 || lastCursor == 1) {
      lcdClrPage(2);
      font708WriteStr(2,  0, 0, menuLine(1), curCursor == 1);
    }
    if(!cursorOnly || curCursor == 2 || lastCursor == 2) {
      lcdClrPage(3);
      font708WriteStr(3,  2, 0,  menuLine(2), curCursor == 2);
    }
    if(!cursorOnly || curCursor == 2 || lastCursor == 2
                   || curCursor == 3 || lastCursor == 3) {
      lcdClrPage(4);
      font708WriteStr(9, -6, 0, menuLine(2), curCursor == 2);
      font708WriteStr(4,  3, 0, menuLine(3), curCursor == 3);
    }
    if(!cursorOnly || curCursor == 3 || lastCursor == 3
                   || curCursor == 4 || lastCursor == 4) {
      lcdClrPage(5);
      font708WriteStr(9, -5, 0, menuLine(3), curCursor == 3);
      font708WriteStr(5,  6, 0, menuLine(4), curCursor == 4);
    }
    if(!cursorOnly || curCursor == 4 || lastCursor == 4) {
      lcdClrPage(6);
      font708WriteStr(6, -2, 0, menuLine(4), curCursor == 4);
    }
    if(!cursorOnly || curCursor == 5 || lastCursor == 5) {
      lcdClrPage(7);
      font708WriteStr(7,  0, 0, menuLine(5), curCursor == 5);
    }
  } else {
    font708WriteStr(2,  0, 0, menuLine(1), false);
    font708WriteStr(3,  2, 0, menuLine(2), false);
    font708WriteStr(9, -6, 0, menuLine(2), false);
    font708WriteStr(4,  3, 0, menuLine(3), false);
    font708WriteStr(9, -5, 0, menuLine(3), false);
    font708WriteStr(5,  6, 0, menuLine(4), false);
    font708WriteStr(6, -2, 0, menuLine(4), false);
    font708WriteStr(7,  0, 0, menuLine(5), false);
  }
}

const uint8 cursorLines[] = {
  4,  // mainMenu
  3,  // settingsMenu
  4,  // pasteSettingsMenu
};

const uint8 cursorDist[] = {
  1,  // mainMenu
  1,  // settingsMenu
  2,  // pasteSettingsMenu
};

const uint8 parentMenu[menuCnt] = {
  mainMenu,      // mainMenu
  mainMenu,      // settingsMenu
  settingsMenu,  // pasteSettingsMenu
};

const uint8 menuSelScreen[menuCnt][menuLineCnt] = {
  {pasteScreen, pickScreen, inspectScreen, settingsMenu}, // mainMenu
  {pasteSettingsMenu},                                    // settingsMenu
};

uint8 defCursByMenu[menuCnt];

bool scrCursorUp(bool oneOnly) {
  uint8 dist = (oneOnly ? 1 : cursorDist[curScreen]);
  if(curCursor > dist) {
    curCursor -= dist;
    drawScreen(true);
    lastCursor = curCursor;
    defCursByMenu[curScreen] = curCursor;
    return true;
  } else
    return false;
}

bool scrCursorDown(bool oneOnly) {
  uint8 dist = (oneOnly ? 1 : cursorDist[curScreen]);
  if(curCursor < cursorLines[curScreen] - dist + 1) {
    curCursor += dist;
    drawScreen(true);
    lastCursor = curCursor;
    defCursByMenu[curScreen] = curCursor;
    return true;
  } else
    return false;
}

uint8 editingOption = 0;

void openOptionField(uint8 optCode) {
  editingOption = optCode;
  scrCursorDown(true);
}