
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
void lcdClrPageBuf();
void lcdClrAll();
void lcdSendPageBuf();
void lcdShowLogo();
void lcdWriteStr(uint16 font, uint8 page, int8 rowOfs, uint8 col, 
                              const char *str, bool cursor);
void lcdShowMenuPage(const char *heading, const char *line1, const char *line2, 
                     const char *line3  , const char *line4, const char *line5,
                     uint8 cursor);
void lcdTest();

#endif	/* LCD_H */

