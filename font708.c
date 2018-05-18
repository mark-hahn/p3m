
#include <xc.h>
#include "font708.h"
#include "util.h"
#include "lcd.h"

// font708 is defined in font708.asm
extern const uint16 font0708;

uint16 font708Addr;

void initFont708() {
  font708Addr = (uint16) &font0708;
}

uint8 chrBuf[9];

char font708chrShrink2[]  = {' ', 'i', 'l', '('};
char font708chrShrink1[]   = {'j', 'H'};
//char font708chrExpand1[]   = {};
char font708chrExpand2[]  = {'M', 'W', 'm', 'w'};


void font708Chr2pageBuf(char ascii, int8 rowOfs, bool cursor) {
    if(ascii < 32) ascii += (32 - 8 - 2);
    
    uint8 wid = 7;
    for(uint8 i=0; i < sizeof(font708chrShrink2); i++)
        if (ascii == font708chrShrink2[i]) wid = 5;
    for(uint8 i=0; i < sizeof(font708chrShrink1); i++)
        if (ascii == font708chrShrink1[i]) wid = 6;
//    for(uint8 i=0; i < sizeof(font708chrExpand1); i++)
//        if (ascii == font708chrExpand1[i]) wid = 8;
    for(uint8 i=0; i < sizeof(font708chrExpand2); i++)
        if (ascii == font708chrExpand2[i]) wid = 9;
    if(lcdPageBufIdx + wid > 128) return;
    
    uint16 romOfs = ((uint16) ascii - 32 + 8) * 4;
    uint16 word0 = getRomWord(font708Addr + romOfs);
    uint16 word1 = getRomWord(font708Addr + romOfs+1);
    uint16 word2 = getRomWord(font708Addr + romOfs+2);
    uint16 word3 = getRomWord(font708Addr + romOfs+3);
    
    chrBuf[0] = ((word0 & 0x3fc0) >> 6);
    chrBuf[1] = ((word0 & 0x003f) << 2) | (word1 >> 12);
    chrBuf[2] = ((word1 & 0x0ff0) >> 4);
    chrBuf[3] = ((word1 & 0x000f) << 4) | ((word2 & 0x3c00) >> 10);
    chrBuf[4] = ((word2 & 0x03fc) >> 2);
    chrBuf[5] = ((word2 & 0x0003) << 6) | ((word3 & 0x3f00) >> 8);
    chrBuf[6] = word3 & 0x00ff;
    chrBuf[7] = 0;
    chrBuf[8] = 0;
    
    for(uint8 i=0; i < wid; i++) {
        uint8 byte = chrBuf[i];
        if(cursor) byte = ~byte;
        if(rowOfs < 0) byte >>= -rowOfs;
        if(rowOfs > 0) byte <<=  rowOfs;
        lcdPageBuf[lcdPageBufIdx] |= byte;
        lcdPageBufIdx++;
    }
}

void font708WriteStr(uint8 page, int8 rowOfs, uint8 col, 
                                 const char *str, bool cursor){
    lcdWriteStr(708, page, rowOfs, col, str, cursor);
}

