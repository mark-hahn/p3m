#ifndef SCREENS_H
#define	SCREENS_H

#include "util.h"
//#include "action.h"

extern uint8 curScreen;;
extern uint8 curCursor;
extern uint8 editingOption;

#define menuLineCnt 5

#define splashScreenIdx 255

#define menuIdxStart     0
#define menuIdxEnd       3
#define screenIdxStart   3

enum menusAndScreens {
  // menuIdxStart
  mainMenu,           // 0
  settingsMenu,       // 1
  pasteSettingsMenu,  // 2

  // screenIdxStart
  pwrOffScrn,         // 3
  menuHelp,           // 4
  menuHelp2,          // 5
  menuHelp3,          // 6

  pasteScreen,        // 7
  pickScreen ,        // 8
  inspectScreen,      // 9
    
  screenIdxEnd
};

#define menuCnt        ( menuIdxEnd   -     menuIdxStart)
#define screenIdxLen   ( screenIdxEnd -   screenIdxStart)
#define screenCnt screenIdxEnd

        
void initScreens();
void initCursor();
void drawScreen(uint8 menu, bool screenOnly, bool cursorOnly);
void redrawScreen();
void scrCursorUp(bool oneOnly);
void scrCursorDown(bool oneOnly);
void openOptionField(uint8 optCode);

#endif	/* SCREENS_H */

