
#include "screens.h"
#include "lcd.h"
#include "font708.h"
#include "font813.h"

// icons 
//  \x80\x81 square button
//  \x82\x83 left rocker
//  \x84\x85 right rocker
//  \x86\x87 top left
//  \x88\x89 bot left
//  \x8a\x8b top right
//  \x8c\x8d bot right

const char *string[stringsCount] = {
    "",                           // blankStr
    "MAIN MENU",                   // mainMenuStr
    ">Paste",                      // pasteStr
    ">Pick / Place",               // pickStr
    ">Inspect",                    // inspectStr
    ">Settings",                   // settingsStr
    "  (Press\x80\x81 for help)",  // menuHelpStr
    
    "MENU HELP",                  // helpMenuStr
    " --- Symbols ---",             // hm1Str 
    "\x80\x81 Leftmost Button",     // hm2Str 
    "\x82\x83 Left Switch",         // hm3Str 
    "\x84\x85 Right Switch",        // hm4Str 
    "           (Press\x80\x81)",   // hm5Str
    
     "MENU HELP Cntd.",           // helpMenu2Str
    "\x86\x87 Left Switch Up",      // hm6Str 
    "\x88\x89 Left Switch Dn",      // hm7Str 
    "\x8a\x8b Right Switch Up",     // hm8Str 
    "\x8c\x8d Right Switch Dn",     // hm9Str 

    " --- Navigation ---",          // hm10Str 
    "\x82\x83 Cursor Up/Down",      // hm11Str 
    "\x8a\x8b Back",                // hm12Str,
    "\x8c\x8d Select",              // hm13Str,
    
    " When in any menu, ",           // hm14Str 
    " \x80\x81 will take you",       // hm15Str 
    " back to the MAIN",             // hm16Str 
    " MENU."                         // hm17Str 
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
    
   {helpMenu2Str, // menuHelp3
    hm14Str,
    hm15Str,
    hm16Str,
    hm17Str,
    hm5Str}
};

uint8 cursor     = 1;
uint8 lastCursor = 1;
uint8 lastMenu   = 0;

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

void scrCursorDown() {
  if(cursor < 5) {
    cursor++;
    scrRedrawMenu(lastMenu);
    lastCursor = cursor;
  }
}

