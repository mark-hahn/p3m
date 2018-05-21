#ifndef SCREENS_H
#define	SCREENS_H

#include "util.h"

extern uint8 curMenu;;
extern uint8 curCursor;

enum menus {
    mainMenu = 0,
    settingsMenu,      // 1
    pasteSettingsMenu, // 2
    menuHelp,      
    menuHelp2,     
    menuHelp3,     
    pasteScreen,   
    pickScreen ,   
    inspectScreen, 
    menusCount
};


void initScreens();
void initCursor();
void scrDrawMenu(uint8 menu, bool screenOnly, bool cursorOnly);
void scrRedrawMenu();
void scrCursorUp();
void scrCursorDown();
void openOptionField(uint8 optCode);

#endif	/* SCREENS_H */

