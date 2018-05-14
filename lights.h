#ifndef LIGHTS_H
#define	LIGHTS_H

#include "util.h"

#define lgtsI2cAddr   0x41
#define lgtsConfigCmd 0x03
#define lgtsDataCmd   0x01

void lgtsInit();
void lgtsSet(uint8 val);
void lgtsDemo();

#endif	/* LIGHTS_H */

