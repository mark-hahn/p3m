
#include "screens.h"
#include "lcd.h"
#include "font708.h"
#include "font813.h"

// icons  (line in asterisk text file)
//  ~ square button  846
//  ` left rocker    
//  \ right rocker
//  @ top left
//  # bot left
//  $ top right
//  ^ bot right

const char *string[stringsCount] = {
    "",                      // blankStr
    "MAIN MENU",             // mainMenuStr
    ">Paste",                 // pasteStr
    ">Pick / Place",          // pickStr
    ">Inspect",               // inspectStr
    ">Settings",              // settingsStr
    "Press ~ for menu help"  // menuHelpStr
};

uint8 menuLines[menusCount][6] = {
   {mainMenuStr,
    pasteStr,
    pickStr,
    inspectStr,
    settingsStr,
    menuHelpStr}
};

uint8 cursor     = 1;
uint8 lastCursor = 1;
uint8 lastMenu   = 0;

void scrDrawMenu(uint8 menu, bool cursorOnly) {
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
}

void scrRedrawMenu(uint8 menu) {
  scrDrawMenu(menu, true);
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

