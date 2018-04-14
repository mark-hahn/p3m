#ifndef FONT708_H
#define	FONT708_H

void initFont708();
void font708Chr2pageBuf(uint8 ascii, int8 rowOfs, bool cursor);
void font708WriteStr(uint8 page, int8 rowOfs, uint8 col, 
                                 const char *str, bool cursor, char bullet);

#endif	/* FONT708_H */

