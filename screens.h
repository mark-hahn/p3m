#ifndef SCREENS_H
#define	SCREENS_H

#include "util.h"

enum menus {
    mainMenu  = 0,
    menuHelp  = 1,
    menuHelp2 = 2,
    menuHelp3 = 3,
    menuHelp4 = 4,    
    menusCount
};

enum strings {
    blankStr = 0,
    mainMenuStr,
    pasteStr,
    pickStr,
    inspectStr,
    settingsStr,
    menuHelpStr,
    helpMenuStr,
    hm1Str,
    hm2Str,
    hm3Str,
    hm4Str,
    hm5Str,
    helpMenu2Str,
    hm6Str,
    hm7Str,
    hm8Str,
    hm9Str,
    hm10Str,
    hm11Str,
    hm12Str,
    hm13Str,
    hm14Str,
    hm15Str,
    hm16Str,
    hm17Str,
    stringsCount
};

extern const char *string[stringsCount];
extern uint8 menuLines[menusCount][6];

void scrDrawMenu(uint8 menu, bool screenOnly, bool cursorOnly);
void scrRedrawMenu(uint8 menu);
void scrCursorUp();
void scrCursorDown();

#endif	/* SCREENS_H */

