
#include "util.h"
#include "lcd.h"
#include "i2c.h"
#include "logotable.h"

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

void lcdClrBuf() {
    for(uint8 page=0; page<8; page++) {
        lcdSendCmd(0xb0 + page);
        lcdSendCmd(0x00); // col idx<3:0> -> 0
        lcdSendCmd(0x10); // col idx<7:4> -> 0
        for(uint8 col=0; col < 132; col++) {
            lcdSendData(0); 
        }
    }
}

uint8 page, colIdx, word, wordIdx, pixel;

void addBitsToWord(uint16 len) {
    for(int i = 0; i < len;  i++) {
        word >>= 1;
        word |= (pixel << 7);
        if(++wordIdx == 8) {
            lcdSendData(word);
            if(++colIdx == 128) {
               colIdx = 0;
                if(++page == 8) return;
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

void lcdTest() {
//        lcdSendCmd(0xa5); // Set Entire Display On
//        delayMs(1000);
//        lcdSendCmd(0xa4); // display graphics buffer
//        delayMs(1000);
    
    // set col start address to 0
    lcdSendCmd(0x00);
    lcdSendCmd(0x10);
    for(uint8 row8 = 0; row8 < 8; row8++) {
        lcdSendCmd(0xb0 + row8);
        for(uint8 col=0; col < 128; col++) {
            lcdSendData(row8+col);
        }
        // right 4 invisible pixels (1106 chip only)
        // SHOULD BE CONDITIONAL ON SETTINGS BIT     TODO
        for(uint8 col=0; col < 4; col++) {
            lcdSendData(0);
        }
    }    
    while(1);
}
