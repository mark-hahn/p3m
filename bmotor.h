#ifndef BMOTOR_H
#define	BMOTOR_H

#define bmotPinsB 0x39
#define bmotPinsC 0x30

#define dirLAT LATB0
#define ms3LAT LATB3
#define ms2LAT LATB4
#define ms1LAT LATB5

#define dstepLAT LATC4
#define tstepLAT LATC5
#define faultLAT LATC7 // not used -- pin used for debug

#define expReset 0x20  // reset pin on expansion port B

void bmotorInit();
void bmotorTest();


#endif	/* BMOTOR_H */

