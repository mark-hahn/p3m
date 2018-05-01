#ifndef BMOTOR_H
#define	BMOTOR_H

#define useFaultForDebug false

#define bmotPinsB 0x79   // set all motor pins to output (except fault)
#define bmotPinsC 0xe0   // set to output
#define faultTRIS TRISB7 // also used as debug pin

#define dirLAT    LATB0
#define ms1LAT    LATB5
#define ms2LAT    LATB4
#define ms3LAT    LATB3
#define resetLAT  LATB6

#define faultLAT  LATB7
#define faultPORT RB7

#define rstepLAT LATC5
#define tstepLAT LATC6
#define sstepLAT LATC7

#define expReset 0x20  // reset pin on expansion port B

void bmotorInit();
void bmotorTest();


#endif	/* BMOTOR_H */

