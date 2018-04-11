
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

uint16 getRomWord(uint16 addr) {
    NVMCON1bits.NVMREGS = 0;
    NVMADRL = addr & 0xff;
    NVMADRH = addr >> 8;
    NVMCON1bits.RD = 1;
    return  ((uint16) NVMDATH << 8) | NVMDATL;   
}
