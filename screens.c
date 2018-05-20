
#include "screens.h"
#include "lcd.h"
#include "font708.h"
#include "font813.h"
#include "strings.h"

uint8 menuLines[menusCount][6] = {
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
    sm2Str,
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

uint8 cursorLines[menusCount] = {
  4,  // mainMenu
  3,  // settingsMenuStr
  0,0,0,0
};

uint8 cursor, lastCursor, lastMenu;;

void initCursor() {
  cursor = 1;
  lastCursor = 1;
}
void initScreens() {
  initCursor();
  lastMenu   = 0;
}

void scrDrawMenu(uint8 menu, bool screenOnly, bool cursorOnly) {
    lastMenu = menu;        
    
    if(!cursorOnly) {
      lcdClrPage(0);
      lcdClrPage(1);
      font813WriteStr(0,  0, 0, romStr(menuLines[menu][0]));
      font813WriteStr(1, -8, 0, romStr(menuLines[menu][0]));
    }
    if(!screenOnly) {
      if(!cursorOnly || cursor == 1 || lastCursor == 1) {
        lcdClrPage(2);
        font708WriteStr(2,  0, 0, romStr(menuLines[menu][1]), cursor == 1);
      }
      if(!cursorOnly || cursor == 2 || lastCursor == 2) {
        lcdClrPage(3);
        font708WriteStr(3,  2, 0,  romStr(menuLines[menu][2]), cursor == 2);
      }
      if(!cursorOnly || cursor == 2 || lastCursor == 2
                     || cursor == 3 || lastCursor == 3) {
        lcdClrPage(4);
        font708WriteStr(9, -6, 0, romStr(menuLines[menu][2]), cursor == 2);
        font708WriteStr(4,  3, 0, romStr(menuLines[menu][3]), cursor == 3);
      }
      if(!cursorOnly || cursor == 3 || lastCursor == 3
                     || cursor == 4 || lastCursor == 4) {
        lcdClrPage(5);
        font708WriteStr(9, -5, 0, romStr(menuLines[menu][3]), cursor == 3);
        font708WriteStr(5,  6, 0, romStr(menuLines[menu][4]), cursor == 4);
      }
      if(!cursorOnly || cursor == 4 || lastCursor == 4) {
        lcdClrPage(6);
        font708WriteStr(6, -2, 0, romStr(menuLines[menu][4]), cursor == 4);
      }
      if(!cursorOnly || cursor == 5 || lastCursor == 5) {
        lcdClrPage(7);
        font708WriteStr(7,  0, 0, romStr(menuLines[menu][5]), cursor == 5);
      }
    } else {
      font708WriteStr(2,  0, 0, romStr(menuLines[menu][1]), false);
      font708WriteStr(3,  2, 0, romStr(menuLines[menu][2]), false);
      font708WriteStr(9, -6, 0, romStr(menuLines[menu][2]), false);
      font708WriteStr(4,  3, 0, romStr(menuLines[menu][3]), false);
      font708WriteStr(9, -5, 0, romStr(menuLines[menu][3]), false);
      font708WriteStr(5,  6, 0, romStr(menuLines[menu][4]), false);
      font708WriteStr(6, -2, 0, romStr(menuLines[menu][4]), false);
      font708WriteStr(7,  0, 0, romStr(menuLines[menu][5]), false);
    }
}

void scrRedrawMenu(uint8 menu) {
  scrDrawMenu(menu, false, true);
}

void scrCursorUp() {
  if(cursor > 1) {
    cursor--;
    scrRedrawMenu(lastMenu);
    lastCursor = cursor;
  }
}

void scrCursorDown(uint8 menuIdx) {
  if(cursor < cursorLines[menuIdx]) {
    cursor++;
    scrRedrawMenu(lastMenu);
    lastCursor = cursor;
  }
}

