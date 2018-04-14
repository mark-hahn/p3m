#ifndef SCREENS_H
#define	SCREENS_H

#include "util.h"

#define bulletChr '>'

enum strings {
    mainMenuStr = 0,
    calibrateStr,
    pasteStr,
    pickStr,
    inspectStr,
    settingsStr,
    stringsCount
};

extern const char *string[stringsCount];

enum menus {
    mainMenu = 0,
//    calibrateMenu,
//    settingsMenu,
    menusCount
};

extern uint8 menuLines[menusCount][6];

enum screens {
    pasteScreen = 0,
    pickScreen,
    inspectScreen
};

void scrDrawMenu(uint8 menu, bool cursorOnly);
void scrRedrawMenu(uint8 menu);
void scrCursorUp();
void scrCursorDown();

#endif	/* SCREENS_H */

