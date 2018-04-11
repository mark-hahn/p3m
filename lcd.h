
#ifndef LCD_H
#define	LCD_H

#include "util.h"

#define i2cLcdAddr      0x3C

#define lcdCmdCtrl      0x80
#define lcdDataCtrl     0xc0
#define lcdContDataCtrl 0x40

void lcdInit();
void lcdSendCmdByte(uint8 cmd);
void lcdSendCmd(uint8 cmd);
void lcdSendData(uint8 data);
void lcdClrBuf();
void lcdShowLogo();
void lcdTest();

#endif	/* LCD_H */

