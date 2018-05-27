#ifndef STATE_H
#define	STATE_H

#include "util.h"
#include "panel.h"
#include "screens.h"

#define logoMs 2000

enum actions {
  noOp,
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

void actionChk(uint8 switchMask);
void handleSwUpDown(uint8 switchMask, bool swUp);
void doAction(uint8 action);
void poweredUp();

#endif	/* STATE_H */

