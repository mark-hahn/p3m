

#include <xc.h>
#include "util.h"
#include "lcd.h"

// font813 is defined in font813.as
extern const uint16 font813;

uint16 font813Addr;

void initFont813() {
  font813Addr = (uint16) &font813;
}

void font813Chr2pageBuf(uint8 ascii, int8 rowOfs) {
    uint16 romOfs = (uint16) (ascii - 32) * 8;
    for(uint8 i = 0; i < 8; i++) {
        uint16 word = getRomWord(font813Addr + romOfs++);
        if(rowOfs < 0) word >>= -rowOfs;
        if(rowOfs > 0) word <<=  rowOfs;
        lcdPageBuf[lcdPageBufIdx] |= (word & 0xff);
        lcdPageBufIdx++;
    }   
}

void font813WriteStr(uint8 page, int8 rowOfs, uint8 col, const char *str) {
    lcdWriteStr(813, page, rowOfs, col, str, false);
}