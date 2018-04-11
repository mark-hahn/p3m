
#include <xc.h>
#include "util.h"
#include "lcd.h"

// font708 is defined in font708.as
extern const uint16 font708;

uint16 font708Addr;
uint16 font708Index;
uint16 font708Word;

void initFont708() {
  font708Addr = (uint16) &font708;
}

uint8 font708Chr2pageBuf(uint8 ascii) {
    uint16 romOfs = (uint16) (ascii - 32) * 4;
    uint16 word0 = getRomWord(font708Addr + romOfs);
    uint16 word1 = getRomWord(font708Addr + romOfs+1);
    uint16 word2 = getRomWord(font708Addr + romOfs+2);
    uint16 word3 = getRomWord(font708Addr + romOfs+3);
//  word0: 00000000111111 word1: 11222222223333 
//  word2: 33334444444455 word3: 55555566666666
    lcdPageBuf[lcdPageBufIdx++] = ((word0 & 0x3fc0) >> 6);
    lcdPageBuf[lcdPageBufIdx++] = ((word0 & 0x003f) << 2) | (word1 >> 12);
    lcdPageBuf[lcdPageBufIdx++] = ((word1 & 0x0ff0) >> 4);
    lcdPageBuf[lcdPageBufIdx++] = ((word1 & 0x000f) << 4) | ((word2 & 0x3c00) >> 10);
    lcdPageBuf[lcdPageBufIdx++] = ((word2 & 0x03fc) >> 2);
    lcdPageBuf[lcdPageBufIdx++] = ((word2 & 0x0003) << 6) | ((word3 & 0x3f00) >> 8);
    lcdPageBuf[lcdPageBufIdx++] =   word3 & 0x00ff;
    return 7;
}

void font708WriteStr(uint8 page, uint8 col, char *str){
    lcdWriteStr(708, page,  col, str, false);
}

