#ifndef STATE_H
#define	STATE_H

#include "util.h"
#include "panel.h"
#include "screens.h"

#define logoMs 2000

enum actions {
  noOp,
  pwrOnAction,
  pwrOffAction,
  startLogoAction,
  cursorUpAction,
  cursorDownAction,
  settingsUpAction,
  settingsDownAction,
  escMenuAction,
  okMenuAction,
  
  actionCount  // go to screen actions start here
};

#define scrOfs actionCount

extern uint16 logoStartTimeStamp;

void timeoutChk(uint8 switchMask);
void handleSwUpDown(uint8 switchMask, bool swUp);
void doAction(uint8 action);

#endif	/* STATE_H */

