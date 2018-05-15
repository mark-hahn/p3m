
#include <xc.h>
#include "util.h"
#include "bmotor.h"
#include "lcd.h"

bool lcdDbgTogVal;

void utilInit() {
#ifdef FAULT_DEBUG
      faultLat  = 0;
      faultTRIS = 0; // also used as debug pin
#endif
#ifdef LCD_DEBUG
      lcdDbgTogVal = 0;
#endif
      
    T0ASYNC             = 0;   // sync clock
    T016BIT             = 1;   // 16-bit counter
    T0CON1bits.T0CS     = 5;   // src clk is MFINTOSC (0.5 mhz)
    T0CON1bits.T0CKPS   = 6;   // prescaler  is 1:64 (8 khz, 128 usecs)
    T0EN                = 1;   // enable timer0
}

void dbg() {
#ifdef FAULT_DEBUG
      faultLat = 1;
      volatile int x=1;
      faultLat = 0;
#endif
}

void dbgToggle() {
#ifdef FAULT_DEBUG
   faultLat = !faultLat;
#endif
#ifdef LCD_DEBUG
   char tf[2]; tf[1] = 0;
   if( lcdDbgTogVal) tf[0] = 'T';
   if(!lcdDbgTogVal) tf[0] = 'F';
   lcdDbgStr(7, tf);
   lcdDbgTogVal = !lcdDbgTogVal;
#endif
}

uint16 timer() {
  uint8 low = TMR0L;
  return(TMR0H << 8) | low;
}

void delay128Usecs(uint16 ticks) {
  uint16 start = timer();
  while (timer() != (start + ticks));
}

void delayMs(uint16 ms) {
  for(uint16 i=0; i < ms; i++)
    delay128Usecs(8);
}

uint16 getRomWord(uint16 addr) {
    NVMCON1bits.NVMREGS = 0;
    NVMADRL = addr & 0xff;
    NVMADRH = addr >> 8;
    NVMCON1bits.RD = 1;
    return  ((uint16) NVMDATH << 8) | NVMDATL;   
}
