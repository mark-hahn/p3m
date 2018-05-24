#ifndef BMOTOR_H
#define	BMOTOR_H

#define bmotPinsB 0x79   // set all motor pins to output (except fault)
#define bmotPinsC 0xe0   // set to output
#define faultTRIS TRISB7 // also used as debug pin

#define dirLAT    LATB0
#define ms1LAT    LATB5
#define ms2LAT    LATB4
#define ms3LAT    LATB3
#define resetLAT  LATB6

#define faultLat  LATB7
#define faultPORT RB7

#define rstepLAT  LATC5
#define tstepLAT  LATC6
#define sstepLAT  LATC7

void bmotorInit();
void bmotorTest();
void bmotInt(uint8 motorIdx);


#endif	/* BMOTOR_H */

