

#ifndef SMOT_H
#define	SMOT_H

#include <xc.h>
#include "main.h"

// motor indexes
#define smote 0
#define smotp 1
#define smotf 2

void smotInit();
void smotOnOff(uint8 motor, bool on);
void smotStep(uint8 motor, int dir);
void smotTest(uint16 pps, int dir);

#endif	/* SMOT_H */

