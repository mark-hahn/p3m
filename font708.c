
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
char font708chrShrink2[]  = {' ', 'i', 'l'};
char font708chrShrink1[]   = {'j', 'H'};
//char font708chrExpand1[]   = {};
char font708chrExpand2[]  = {'M', 'W'};


uint8 font708Chr2pageBuf(char ascii) {
    uint8 wid = 7;
    for(uint8 i=0; i < sizeof(font708chrShrink2); i++)
        if (ascii == font708chrShrink2[i]) wid = 5;
    for(uint8 i=0; i < sizeof(font708chrShrink1); i++)
        if (ascii == font708chrShrink1[i]) wid = 6;
//    for(uint8 i=0; i < sizeof(font708chrExpand1); i++)
//        if (ascii == font708chrExpand1[i]) wid = 8;
    for(uint8 i=0; i < sizeof(font708chrExpand2); i++)
        if (ascii == font708chrExpand2[i]) wid = 9;
    if(lcdPageBufIdx + wid > 128) return 0;
    
    uint16 romOfs = (uint16) (ascii - 32) * 4;
    uint16 word0 = getRomWord(font708Addr + romOfs);
    uint16 word1 = getRomWord(font708Addr + romOfs+1);
    uint16 word2 = getRomWord(font708Addr + romOfs+2);
    uint16 word3 = getRomWord(font708Addr + romOfs+3);
    lcdPageBuf[lcdPageBufIdx++] = ((word0 & 0x3fc0) >> 6);
    lcdPageBuf[lcdPageBufIdx++] = ((word0 & 0x003f) << 2) | (word1 >> 12);
    lcdPageBuf[lcdPageBufIdx++] = ((word1 & 0x0ff0) >> 4);
    lcdPageBuf[lcdPageBufIdx++] = ((word1 & 0x000f) << 4) | ((word2 & 0x3c00) >> 10);
    lcdPageBuf[lcdPageBufIdx++] = ((word2 & 0x03fc) >> 2);
    if(wid > 5)
      lcdPageBuf[lcdPageBufIdx++] = ((word2 & 0x0003) << 6) | ((word3 & 0x3f00) >> 8);
    if(wid > 6)
      lcdPageBuf[lcdPageBufIdx++] = word3 & 0x00ff;
    if(wid > 7)
      lcdPageBuf[lcdPageBufIdx++] = 0;
    if(wid > 8)
      lcdPageBuf[lcdPageBufIdx++] = 0;
    return wid;
}

void font708WriteStr(uint8 page, uint8 col, const char *str){
    lcdWriteStr(708, page,  col, str, false);
}

