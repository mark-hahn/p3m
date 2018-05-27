#ifndef STATE_H
#define	STATE_H

#include "util.h"
#include "exp-panel.h"
#include "screens.h"

#define logoMs 2000

enum actions {
  noOp,
  pwrOffAction,
  menuUpAction,
  menuDownAction,
  settingsUpAction,
  settingsDownAction,
  escAtion,
  okAction,
  
  actionCount  // go to screen actions start here
};

#define scrOfs actionCount

extern uint8 actionTable[screenCnt][3][switchesCount];
extern volatile bool swHoldWaiting[6];
extern volatile uint16 swDownTimestamp[6];
   
void doAction(uint8 action);
void handleSwUpDown(uint8 switchMask, bool swUp);
void handleSwHoldStart(uint8 switchMask);

#endif	/* STATE_H */

