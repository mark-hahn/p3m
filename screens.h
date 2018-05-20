#ifndef SCREENS_H
#define	SCREENS_H

#include "util.h"

extern uint8 cursor;

enum menus {
    mainMenu      = 0,
    settingsMenu,  // 1
    menuHelp,      // 2
    menuHelp2,     // 3
    menuHelp3,     // 4
    pasteScreen,   // 5
    pickScreen ,   // 6
    inspectScreen, // 7
    menusCount
};

void initScreens();
void initCursor();
void scrDrawMenu(uint8 menu, bool screenOnly, bool cursorOnly);
void scrRedrawMenu(uint8 menu);
void scrCursorUp();
void scrCursorDown(uint8 menuIdx);

#endif	/* SCREENS_H */

