
#include <xc.h>
#include "util.h"

// font708 is defined in font708.asm
extern const uint16 font708;

uint16 font708Addr;
uint16 font708Index;
uint16 font708Word;

void initFont708() {
  font708Addr = (uint16) &font708;
}

uint8 writeFont708Cols(uint8 ascii) {
    uint16 wordOfs = ((ascii - 32) * 4)/7;
    uint16 byteOfs = wordOfs * 4; // ???
    
//    if((font708Index & 1) == 0) {
//        uint16 addr = font708Addr + ofs;
//        NVMCON1bits.NVMREGS = 0;
//        NVMADRL = addr & 0xff;
//        NVMADRH = addr >> 8;
//        NVMCON1bits.RD = 1;
//        font708Word = ((uint16) NVMDATH << 8) | NVMDATL;   
//        font708Index++;
//        return font708Word >> 7;
//    } else {
//        font708Index++;
//        return font708Word & 0x7f;
//    }
}


