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
  uint16 count;    // pulse count, 65535 is infinity; 0 means idle
  uint8  ustep;    // 0..5; (1 / (2^ustep))
  bool   fwdDir;   // true is fwd, false is reverse
  uint8  rateCount;// pulse period is (1984/rateCount) * 84 usecs
  uint8  intCtr;   // interrupt counter
};

void bmotorInit();
void startBmot(uint8 motor, uint8 ustep, bool fwdDir, uint16 pps, uint16 count);
void stopBmot(uint8 motor);
void bmotAllPwrOff();
void bmotInt(uint8 motor);

#endif	/* BMOTOR_H */

