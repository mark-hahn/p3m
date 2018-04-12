/* 
 * File:   font813.h
 * Author: root
 *
 * Created on April 11, 2018, 1:14 PM
 */

#ifndef FONT813_H
#define	FONT813_H

void initFont813();
void font813Chr2pageBuf(uint8 ascii, int8 rowOfs);
void font813WriteStr(uint8 page, int8 rowOfs, uint8 col, const char *str);

#endif	/* FONT813_H */

