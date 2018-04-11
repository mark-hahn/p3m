

#include <xc.h>
#include "util.h"
#include "lcd.h"

// font813 is defined in font813.as
extern const uint16 font813;

uint16 font813Addr;
uint16 font813Index;
uint16 font813Word;

void initFont813() {
  font813Addr = (uint16) &font813;
}

uint8 font813Chr2pageBuf(uint8 ascii, Boolean page2) {
    uint16 romOfs = (uint16) (ascii - 32) * 8;
    for(uint8 i = 0; i < 8; i++) {
        uint16 word = getRomWord(font813Addr + romOfs);
        lcdPageBuf[lcdPageBufIdx++] = (page2 ? (word & 0x3f) : word >> 6);
    }   
    return 8;
}

void font813WriteStr(uint8 page, uint8 col, char *str) {
    lcdWriteStr(813, page,   col, str, false);
    lcdWriteStr(813, page+1, col, str, true);
}