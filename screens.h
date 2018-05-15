#ifndef SCREENS_H
#define	SCREENS_H

#include "util.h"

enum strings {
    blankStr = 0,
    mainMenuStr,
    pasteStr,
    pickStr,
    inspectStr,
    settingsStr,
    menuHelpStr,
    stringsCount,
};

extern const char *string[stringsCount];

enum menus {
    mainMenu = 0,
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

