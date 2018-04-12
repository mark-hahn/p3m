#ifndef FONT708_H
#define	FONT708_H

void initFont708();
uint8 font708Chr2pageBuf(uint8 ascii);
void font708WriteStr(uint8 page, uint8 col, const char *str);

#endif	/* FONT708_H */

