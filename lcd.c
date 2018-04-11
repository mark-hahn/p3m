
#include "util.h"
#include "lcd.h"
#include "i2c.h"
#include "logotable.h"
#include "font708.h"
#include "font813.h"

uint8 lcdPageBuf[128];
uint8 lcdPageBufIdx;

void lcdSendCmdByte(uint8 cmd) {
    i2cSendByte(lcdCmdCtrl);
    i2cSendByte(cmd);
}

void lcdInit() {
    i2cStartSending(i2cLcdAddr);
    
	lcdSendCmdByte(0xae);//--turn off oled panel
    
	lcdSendCmdByte(0xd5);//--set display clock divide ratio/oscillator frequency
	lcdSendCmdByte(0x80);//--set divide ratio
    
	lcdSendCmdByte(0xa8);//--set multiplex ratio(1 to 64)
	lcdSendCmdByte(0x3f);//--1/64 duty
    
	lcdSendCmdByte(0xd3);//-set display offset
	lcdSendCmdByte(0x00);//-not offset
    
	lcdSendCmdByte(0x8d);//--set Charge Pump enable/disable
	lcdSendCmdByte(0x14);//--set(0x14) enable
    
	lcdSendCmdByte(0x40);//--set start line address
    
	lcdSendCmdByte(0xa6);//--set normal display (not inverted black/white))
    
	lcdSendCmdByte(0xa4);//  Disable Entire Display On
    
	lcdSendCmdByte(0xa1);//--set segment re-map 128 to 0
    
	lcdSendCmdByte(0xC8);//--Set COM Output Scan Direction 64 to 0
    
	lcdSendCmdByte(0xda);//--set com pins hardware configuration
	lcdSendCmdByte(0x12); // 0x12 for 1106?  0x02 for 1306?  --  TODO
    
	lcdSendCmdByte(0x81);//--set contrast control register -- BRIGHTNESS
	lcdSendCmdByte(0xff);
    
	lcdSendCmdByte(0xd9);//--set pre-charge period
	lcdSendCmdByte(0xf1);
    
	lcdSendCmdByte(0xdb);//--set vcomh
	lcdSendCmdByte(0x40);
        
	lcdSendCmdByte(0xaf);//--turn on oled panel

 	i2cStopSending();   
}

void lcdSendCmd(uint8 cmd) {
    i2cStartSending(i2cLcdAddr);
    lcdSendCmdByte(cmd);
    i2cStopSending();   
}

void lcdSendData(uint8 data) {
    i2cStartSending(i2cLcdAddr);
    i2cSendByte(lcdDataCtrl);
    i2cSendByte(data);
    i2cStopSending();   
}

void lcdSendPageBuf(uint8 len) {
    dbg();
    i2cStartSending(i2cLcdAddr);
    i2cSendByte(lcdContDataCtrl);
    for(uint8 i=0; i < len; i++) {
        i2cSendByte(lcdPageBuf[i]);
    }
    i2cStopSending();       
}
void lcdClrBuf() {
    for(uint8 i=0; i<128; i++) lcdPageBuf[i] = 0;
    for(uint8 page=0; page<8; page++) {
        lcdSendCmd(0xb0 + page);
        lcdSendCmd(0x00); // col idx<3:0> -> 0
        lcdSendCmd(0x10); // col idx<7:4> -> 0
        lcdSendPageBuf(128);
    }
}

uint8 page, colIdx, word, wordIdx, pixel;

void addBitsToWord(uint16 len) {
    for(uint8 i = 0; i < len;  i++) {
        word >>= 1;
        word |= (pixel << 7);
        if(++wordIdx == 8) {
            lcdSendData(word);
            if(++colIdx == 128) {
                lcdSendData(0);
                lcdSendData(0);
                lcdSendData(0);
                lcdSendData(0);
                
                if(++page == 8) return;
                colIdx = 0;
                lcdSendCmd(0xb0 + page);
                lcdSendCmd(0x00); // col idx<3:0> -> 0
                lcdSendCmd(0x10); // col idx<7:4> -> 0
            }
            word = wordIdx = 0;
        }
    }
}

void lcdShowLogo() {
    initLogotable();
    page = colIdx = word = wordIdx = pixel = 0;
    lcdSendCmd(0xb0 + page);
    lcdSendCmd(0x00); // col idx<3:0> -> 0
    lcdSendCmd(0x10); // col idx<7:4> -> 0
    while(page < 8) {
      addBitsToWord(getNextLogoRunlen());
      pixel = 1 - pixel;
    }
}

void lcdWriteStr(uint16 font, uint8 page, uint8 col, char *str, Boolean page2) {
    lcdClrBuf();
    lcdPageBufIdx = 0;
    uint8 len = 0;
    for(char* p = str; *p; p++) {
        switch(font) {
            case 708: len += font708Chr2pageBuf(*p); break;           
            case 813: len += font813Chr2pageBuf(*p, page2); break;
        }
    }
    lcdSendCmd(0xb0 + page);
    lcdSendCmd(0x00 + (col & 0x0f));
    lcdSendCmd(0x10 + (col >> 4)); 
    lcdSendPageBuf(len);
}
