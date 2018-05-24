#ifndef BMOTOR_H
#define	BMOTOR_H

#define bmotPinsB 0x79   // set all motor pins to output (except fault)
#define bmotPinsC 0xe0   // set to output
#define resetLAT  LATB6
#define faultLAT  LATB7
#define faultTRIS TRISB7


enum bmotIdx {
  rotationMotor,  // rstep C5
  pinchMotor,     // tstep C6
  zoomMotor,      // sstep C7
};

extern struct bmotStateStruct bmotState[3];

struct bmotStateStruct {
  uint8  ustep;    // 0..5; (1 / (2^ustep))
  bool   fwdDir;   // true is fwd, false is reverse
  uint16 count;    // pulse count, 255 is infinity; 0 means idle
  uint8  rateInc;  // pulse period is rateInc * 96 usecs
};

void bmotorInit();
void bmotInt(uint8 motorIdx);
void setBmotInfo(uint8 motorIdx, uint8 ustep, bool fwdDir, uint16 pps);
void startBmot(uint8 motorIdx, uint16 count);
void stopBmot(uint8 motorIdx);

#endif	/* BMOTOR_H */

