
#include <xc.h>
#include "util.h"
#include "logo.h"

// logotable is defined in logotable.asm
extern const uint16 logotable;

uint16 logoAddr;
uint16 logoIndex;
uint16 logoWord;

void initLogo() {
  logoAddr = (uint16) &logotable;
  logoIndex = 0;
}

uint8 getNext7bitsRunlen() {
    uint16 ofs = logoIndex >> 1;
    if((logoIndex & 1) == 0) {
        uint16 addr = logoAddr + ofs;
        NVMCON1bits.NVMREGS = 0;
        NVMADRL = addr & 0xff;
        NVMADRH = addr >> 8;
        NVMCON1bits.RD = 1;
        logoWord = ((uint16) NVMDATH << 8) | NVMDATL;   
        logoIndex++;
        return logoWord >> 7;
    } else {
        logoIndex++;
        return logoWord & 0x7f;
    }
}

uint16 getNextLogoRunlen() {
    uint16 totalRun = 0;
    uint8 run = getNext7bitsRunlen();
    while(run == 127) {
      totalRun += run;
      run = getNext7bitsRunlen();
    }
    totalRun += run;
    return totalRun;
}
