
#ifndef LCD_H
#define	LCD_H

#include "util.h"

#define i2cLcdAddr      0x3C

#define lcdCmdCtrl      0x80
#define lcdDataCtrl     0xc0
#define lcdContDataCtrl 0x40

extern uint8 lcdPageBuf[128];
extern uint8 lcdPageBufIdx;

void lcdInit();
void lcdSendCmdByte(uint8 cmd);
void lcdSendCmd(uint8 cmd);
void lcdSendData(uint8 data);
void lcdClrPage(uint8 page);
void lcdClrPageBuf();
void lcdClrAll();
void lcdSendPageBuf();
void lcdWriteStr(uint16 font, uint8 page, int8 rowOfs, uint8 col, 
                              const char *str, bool cursor, char bullet);
void lcdDbgStr(uint8 page, const char *str);
void lcdDbgInt(uint8 page, uint8 num);
void lcdOn();
void lcdOff();

#endif	/* LCD_H */

