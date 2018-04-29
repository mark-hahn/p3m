
#include <xc.h>
#include "util.h"
#include "exp-panel.h"
#include "bmotor.h"

void bmotorInit() {
  // half-stepping
  ms3LAT = 1;
  ms2LAT = 0;
  ms1LAT = 0;
  
  // some direction?
  dirLAT = 0;
  
  // all big motor pins are outputs
  TRISB = TRISB & ~bmotPinsB;
  TRISC = TRISC & ~bmotPinsC;

  // start with reset low
  // doesn't work on first board without display connectoed
  expWriteB(1);
}

void bmotorTest() {
  // release reset
  // doesn't work on first board without display connectoed
  expWriteB(expReset);
  
  // right rocker is tweezer, bot open, top close
  // right rocker is direction, top is clockwise
  while(1) {
    uint8 swreg = expReadA();

    tstepLAT = 0;
    delay128Usecs(2);
    
    dstepLAT = 0;
    delay128Usecs(2);
    
    dirLAT = ((swreg & swBotLftMask) == 0);
    delay128Usecs(2);
    
    tstepLAT = 1;//((swreg & swBotLftMask) == 0) || ((swreg & swTopLftMask) == 0);
    delay128Usecs(2);

    dirLAT = ((swreg & swBotRgtMask) == 0);
    delay128Usecs(2);

    dstepLAT = 1;//((swreg & swBotRgtMask) == 0) || ((swreg & swTopRgtMask) == 0);
  }
}

