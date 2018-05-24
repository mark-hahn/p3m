#ifndef STATE_H
#define	STATE_H

#include "util.h"
#include "exp-panel.h"

#define logoMs 2000

enum states {
  noStateChange = 0,
  pwrOffState,        // 1
  splashState,        // 2
  mainState,          // 3
  menuHelpState,      // 4
  menuHelp2State,     // 5
  menuHelp3State,     // 6
  pasteState,         // 7
  pickState,          // 8
  inspectState,       // 9
  settingsState,      // 10
  pasteSettingState,  // 11
  rotateSettingState, // 12
  pinchSettingState,  // 13
  extrudeDistState,   // 14
  extrudeRateState,   // 15
  statesCount,

  upAction,
  upOffAction,
  downAction,
  downOffAction,
  escAction,
  selAction,   
  upOptAction,
  downOptAction, 
  selOptAction
};

extern uint8 nextState[statesCount][2][switchesCount];
        
void initState();
void stateSwitchChange(uint8 switchMask, bool swUp);
void stateEnter(uint8 state);

#endif	/* STATE_H */

