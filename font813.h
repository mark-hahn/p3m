/* 
 * File:   font813.h
 * Author: root
 *
 * Created on April 11, 2018, 1:14 PM
 */

#ifndef FONT813_H
#define	FONT813_H

void initFont813();
uint8 font813Chr2pageBuf(uint8 ascii, Boolean page2);
void font813WriteStr(uint8 page, uint8 col, const char *str);

#endif	/* FONT813_H */

