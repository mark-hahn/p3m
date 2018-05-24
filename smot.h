

#ifndef SMOT_H
#define	SMOT_H

#include <xc.h>
#include "main.h"

// motor indexes
#define smote 0
#define smotp 1
#define smotf 2

#define smotDirFwd +1
#define smotDirBwd -1

#define smoteTris TRISA
#define smotpTris TRISA
#define smotfTris TRISC

#define smoteLat LATA
#define smotpLat LATA
#define smotfLat LATC

void smotInit();
void smotOnOff(uint8 motor, bool on);
void smotStep( uint8 motor, int dir);
void smotTest( uint8 motor, uint16 pps, int dir);
void smotInt(uint8 motorIdx);

#endif	/* SMOT_H */

