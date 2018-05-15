#ifndef STATE_H
#define	STATE_H

#include "util.h"
#include "exp-panel.h"

#define logoMs 2000

enum states {
  noStateChange = 0,
  pwrOffState,    // 1
  splashState,    // 2
  mainState,      // 3
  menuHelpState,  // 4
  menuHelp2State, // 5
  menuHelp3State, // 6
  menuHelp4State, // 7
  statesCount
};

extern uint8 nextState[statesCount][2][switchesCount];
        
void initState();
void stateSwitchChange(uint8 switchMask, bool swUp);
void stateEnter(uint8 state);

#endif	/* STATE_H */

