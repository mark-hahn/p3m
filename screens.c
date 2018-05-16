
#include "screens.h"
#include "lcd.h"
#include "font708.h"
#include "font813.h"

// icons 
//  \x80\x81 square button
//  \x82     empty rocker
//  \x83     top rocker
//  \x84     bot rocker
//  \x85     both rocker
//  \x86 up arrow
//  \x87 dn arrow

const char *string[stringsCount] = {
    "",                            // blankStr
    "MAIN MENU",                   // mainMenuStr
    ">Paste",                      // pasteStr
    ">Pick / Place",               // pickStr
    ">Inspect",                    // inspectStr
    ">Settings",                   // settingsStr
    "  (Press\x80\x81 for help)",  // menuHelpStr
    
    "MENU HELP",                  // helpMenuStr
    "The symbol\x80\x81 is the",    // hm1Str 
    "leftmost button.",             // hm2Str 
    "It takes you back",            // hm3Str 
    "to the MAIN MENU.",            // hm4Str   
    "           (Press\x80\x81)",   // hm5Str
    
    "MENU HELP cont.",            // helpMenu2Str
    "The pair \x82\x82 are on",     // hm6Str 
    "the right. \x85 means",        // hm7Str 
    "press \x86 or \x87 and",       // hm8Str 
    "\x83 means just \x86.",        // hm9Str 

    " --- Navigation ---",          // hm10Str 
    "\x85\x82 Cursor Up/Down",      // hm11Str 
    "\x82\x83 Back",                // hm12Str,
    "\x82\x84 Select",              // hm13Str,
    
    "PASTE MODE",                   // pasteScreenStr
    "\x85\x82 Position Syringe",      // paste1Str
    "\x82\x83 Extrude Paste",         // paste2Str
    "\x82\x84 Retract Paste",         // paste3Str
    "\x80\x81+ \x85\x82 Focus",       // paste4Str
    "\x80\x81+ \x82\x85 Zoom",        // paste5Str
            
    "PICK/PLACE MODE",             // pickScreenStr
    "\x85\x82 Rotate",               // pick1Str
    "\x82\x83 Pinch",                // pick2Str
    "\x82\x84 Release",              // pick3Str
    "\x80\x81+ \x85\x82 Focus",      // pick4Str
    "\x80\x81+ \x82\x85 Zoom"        // pick5Str
};

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
    paste3Str,
    paste4Str,
    paste5Str},
    
   {pickScreenStr, // pickScreen
    pick1Str,
    pick2Str,
    pick3Str,
    pick4Str,
    pick5Str}
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
    const char *line[6];
    for(uint8 i=0; i<6; i++)
      line[i] = string[menuLines[menu][i]];
    if(!cursorOnly) {
      lcdClrPage(0);
      lcdClrPage(1);
      font813WriteStr(0,  0, 0, line[0]);
      font813WriteStr(1, -8, 0, line[0]);
    }
    if(!screenOnly) {
      if(!cursorOnly || cursor == 1 || lastCursor == 1) {
        lcdClrPage(2);
        font708WriteStr(2,  0, 0, line[1], cursor == 1);
      }
      if(!cursorOnly || cursor == 2 || lastCursor == 2) {
        lcdClrPage(3);
        font708WriteStr(3,  2, 0,  line[2], cursor == 2);
      }
      if(!cursorOnly || cursor == 2 || lastCursor == 2
                     || cursor == 3 || lastCursor == 3) {
        lcdClrPage(4);
        font708WriteStr(9, -6, 0, line[2], cursor == 2);
        font708WriteStr(4,  3, 0, line[3], cursor == 3);
      }
      if(!cursorOnly || cursor == 3 || lastCursor == 3
                     || cursor == 4 || lastCursor == 4) {
        lcdClrPage(5);
        font708WriteStr(9, -5, 0, line[3], cursor == 3);
        font708WriteStr(5,  6, 0, line[4], cursor == 4);
      }
      if(!cursorOnly || cursor == 4 || lastCursor == 4) {
        lcdClrPage(6);
        font708WriteStr(6, -2, 0, line[4], cursor == 4);
      }
      if(!cursorOnly || cursor == 5 || lastCursor == 5) {
        lcdClrPage(7);
        font708WriteStr(7,  0, 0, line[5], cursor == 5);
      }
    } else {
      font708WriteStr(2,  0, 0, line[1], false);
      font708WriteStr(3,  2, 0, line[2], false);
      font708WriteStr(9, -6, 0, line[2], false);
      font708WriteStr(4,  3, 0, line[3], false);
      font708WriteStr(9, -5, 0, line[3], false);
      font708WriteStr(5,  6, 0, line[4], false);
      font708WriteStr(6, -2, 0, line[4], false);
      font708WriteStr(7,  0, 0, line[5], false);
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

