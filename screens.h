#ifndef SCREENS_H
#define	SCREENS_H

#include "util.h"

extern uint8 cursor;

enum menus {
    mainMenu      = 0,
    menuHelp      = 1,
    menuHelp2     = 2,
    menuHelp3     = 3,
    pasteScreen   = 4,
    pickScreen    = 5,
    inspectScreen = 6,
    settingsMenu  = 7,
    menusCount
};

void initScreens();
void scrDrawMenu(uint8 menu, bool screenOnly, bool cursorOnly);
void scrRedrawMenu(uint8 menu);
void scrCursorUp();
void scrCursorDown(uint8 menuIdx);

#endif	/* SCREENS_H */

