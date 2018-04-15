#ifndef STATE_H
#define	STATE_H

#include "util.h"
#include "exp.h"

enum states {
  noStateChange = 0,
  pwrOffState,
  splashState,
  mainState,
  statesCount
};

extern uint8 nextState[statesCount][2][switchesCount];
        
void stateSwitchChange(uint8 switchMask, bool swUp);
void stateEnter(uint8 state);

#endif	/* STATE_H */

