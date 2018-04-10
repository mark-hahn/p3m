
#include <xc.h>
#include "util.h"

void dbgInit() {
    LATC7  = 0;
    TRISC7 = 0; // fault line used as debug pin
}

void dbg() {
    LATC7 = 1;
    int x=1;
    LATC7 = 0;
}

void delayMs(uint16 ms) {
    for(uint32 i=0; i < (ms * (uint32) 20); i++);
}
