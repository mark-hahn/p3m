
#include "buzz.h"
#include "util.h"
#include "exp-panel.h"

void beep() {
  delayMs(beepLen);
  expWriteA(~buzzMask);
  delayMs(beepLen);
  expWriteA(buzzMask);
}