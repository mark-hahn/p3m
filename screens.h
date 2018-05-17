#ifndef SCREENS_H
#define	SCREENS_H

#include "util.h"

extern uint8 cursor;

enum menus {
    mainMenu = 0,
    settingsMenu,
    menuHelp,
    menuHelp2,
    menuHelp3,
    pasteScreen,
    pickScreen,
    inspectScreen,
    menusCount
};

void initScreens();
void scrDrawMenu(uint8 menu, bool screenOnly, bool cursorOnly);
void scrRedrawMenu(uint8 menu);
void scrCursorUp();
void scrCursorDown(uint8 menuIdx);

#endif	/* SCREENS_H */

