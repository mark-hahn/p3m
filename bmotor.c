
#include <xc.h>
#include "util.h"
#include "exp-panel.h"
#include "bmotor.h"

void bmotorInit() {
  
#ifdef FAULT_DEBUG
  faultTRIS = 1;
#endif

  ms3LAT = 1; // half-stepping
  ms2LAT = 0;
  ms1LAT = 0;
  
  dirLAT   = 0; // some direction?
  resetLAT = 0; // start with reset low (resetted)
  
  // all big motor pins are outputs
  TRISB = TRISB & ~bmotPinsB;
  TRISC = TRISC & ~bmotPinsC;
  }

bool swPressed(uint8 swreg, uint8 mask) {
  return ((swreg & mask) == 0);
}

void bmotorTest() {
  // release reset on all bmotors
  resetLAT = 1;
  uint16 count = 0;
  // left rocker is direction, top is counter-clockwise
  // right rocker is tweezer, bot open, top close
  while(1) {
    uint8 swreg = expReadA();
//    bool topLftSw = swPressed(swreg, swTopLftMask);
//    bool botLftSw = swPressed(swreg, swBotLftMask);
//    bool topRgtSw = swPressed(swreg, swTopRgtMask);
//    bool botRgtSw = swPressed(swreg, swBotRgtMask);
//    
//    int8 rSpeed = ;
//    int8 tSpeed = ;        
//            
//    if(count++ & 1) {
//      if(rSpeed ==  1) rSpeed = 0;
//      if(rSpeed == -1) rSpeed = 0;
//      if(tSpeed ==  1) tSpeed = 0;
//      if(tSpeed == -1) tSpeed = 0;
//    }
    
    tstepLAT = 0;
    rstepLAT = 0;
    delay128Usecs(1);
    
    dirLAT = ((swreg & swTopLftMask) == 0);
    delay128Usecs(1);
    
    rstepLAT = ((swreg & swBotLftMask) == 0) || ((swreg & swBotRgtMask) == 0);
    delay128Usecs(1);

    dirLAT = ((swreg & swTopRgtMask) == 0);
    delay128Usecs(1);

    tstepLAT = ((swreg & swBotRgtMask) == 0) || ((swreg & swTopRgtMask) == 0);
  }
}

