#ifndef SCREENS_H
#define	SCREENS_H

#include "util.h"
#include "screens.h"

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
  logoScrn,           // 4
  menuHelp,           // 5
  menuHelp2,          // 6
  menuHelp3,          // 7

  pasteScreen,        // 8
  pickScreen ,        // 9
  inspectScreen,      // 10
    
  screenIdxEnd
};

#define menuCnt        ( menuIdxEnd   -     menuIdxStart)
#define screenIdxLen   ( screenIdxEnd -   screenIdxStart)
#define screenCnt screenIdxEnd

extern       uint8 curScreen;;
extern       uint8 curCursor;
extern       uint8 editingOption;
extern const uint8 parentMenu[menuCnt];
extern const uint8 menuSelScreen[menuCnt][5];
        
void initScreens();
void initCursor();
void drawScreen(uint8 screen, bool cursorOnly);
void redrawScreen();
bool scrCursorUp(bool oneOnly);
bool scrCursorDown(bool oneOnly);
void openOptionField(uint8 optCode);

#endif	/* SCREENS_H */

