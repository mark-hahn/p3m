
#include "screens.h"
#include "lcd.h"
#include "font708.h"
#include "font813.h"
#include "strings.h"

uint8 menuLines[menusCount][6] = {
   {mainMenuStr, // mainMenu
    pasteStr,
    pickStr,
    inspectStr,
    settingsStr,
    menuHelpStr},
    
   {helpMenuStr, // menuHelp
    hm1Str,
    hm2Str,
    hm3Str,
    hm4Str,
    hm5Str},
    
   {helpMenu2Str, // menuHelp2
    hm6Str,
    hm7Str,
    hm8Str,
    hm9Str,
    hm5Str},
    
   {helpMenu2Str, // menuHelp3
    hm10Str,
    hm11Str,
    hm12Str,
    hm13Str,
    hm5Str},
    
   {pasteScreenStr, // pasteScreen
    paste1Str,
    paste2Str,
    lightsStr,
    focusStr,
    zoomStr},
    
   {pickScreenStr, // pickScreen
    pick1Str,
    pick2Str,
    lightsStr,
    focusStr,
    zoomStr},
    
   {inspectScreenStr, // inspectScreen
    inspect1Str,
    inspect2Str,
    focusStr,
    zoomStr,
    inspect3Str},
    
   {settingsMenuStr, // inspectScreen
    sm1Str,
    sm2Str,
    sm3Str,
    pasteStr,
    hm5Str}
};

uint8 cursorLines[menusCount] = {
  4,  // mainMenu
  0,0,0,0
};

uint8 cursor, lastCursor, lastMenu;;

void initScreens() {
  cursor = 1;
  lastCursor = 1;
  lastMenu   = 0;
}

void scrDrawMenu(uint8 menu, bool screenOnly, bool cursorOnly) {
    lastMenu = menu;
    uint16 strId[6];
    
    for(uint8 i=0; i<6; i++)
      strId[i] = menuLines[menu][i];
    
    if(!cursorOnly) {
      lcdClrPage(0);
      lcdClrPage(1);
      font813WriteStr(0,  0, 0, romStr(0));
      font813WriteStr(1, -8, 0, romStr(0));
    }
    if(!screenOnly) {
      if(!cursorOnly || cursor == 1 || lastCursor == 1) {
        lcdClrPage(2);
        font708WriteStr(2,  0, 0, romStr(1), cursor == 1);
      }
      if(!cursorOnly || cursor == 2 || lastCursor == 2) {
        lcdClrPage(3);
        font708WriteStr(3,  2, 0,  romStr(2), cursor == 2);
      }
      if(!cursorOnly || cursor == 2 || lastCursor == 2
                     || cursor == 3 || lastCursor == 3) {
        lcdClrPage(4);
        font708WriteStr(9, -6, 0, romStr(2), cursor == 2);
        font708WriteStr(4,  3, 0, romStr(3), cursor == 3);
      }
      if(!cursorOnly || cursor == 3 || lastCursor == 3
                     || cursor == 4 || lastCursor == 4) {
        lcdClrPage(5);
        font708WriteStr(9, -5, 0, romStr(3), cursor == 3);
        font708WriteStr(5,  6, 0, romStr(4), cursor == 4);
      }
      if(!cursorOnly || cursor == 4 || lastCursor == 4) {
        lcdClrPage(6);
        font708WriteStr(6, -2, 0, romStr(4), cursor == 4);
      }
      if(!cursorOnly || cursor == 5 || lastCursor == 5) {
        lcdClrPage(7);
        font708WriteStr(7,  0, 0, romStr(5), cursor == 5);
      }
    } else {
      font708WriteStr(2,  0, 0, romStr(1), false);
      font708WriteStr(3,  2, 0, romStr(2), false);
      font708WriteStr(9, -6, 0, romStr(2), false);
      font708WriteStr(4,  3, 0, romStr(3), false);
      font708WriteStr(9, -5, 0, romStr(3), false);
      font708WriteStr(5,  6, 0, romStr(4), false);
      font708WriteStr(6, -2, 0, romStr(4), false);
      font708WriteStr(7,  0, 0, romStr(5), false);
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

