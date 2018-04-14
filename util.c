
#include <xc.h>
#include "util.h"

void utilInit() {
    LATC7  = 0;
    TRISC7 = 0; // fault line used as debug pin
    
    T0ASYNC             = 0;   // sync clock
    T016BIT             = 0;   // 16-bit counter
    T0CON1bits.T0CS     = 2;   // src clk is HFINTOSC ((8 mhz)
    T0CON1bits.T0CKPS   = 1;   // prescaler  is 1:1 (/256 => 7.8 khz, 127.2 usecs)
    T0CON1bits.T0PS     = 0;   // postscaler is 1:1
    
    TMR0IF = 0;
    T0EN   = 1;   // enable timer0
    TMR0IE = 1;   // enable timer ints
    PEIE   = 1;   // Peripheral Interrupt Enable
    GIE    = 1;   // Global Interrupt Enable  
}

void dbg() {
    LATC7 = 1;
    volatile int x=1;
    LATC7 = 0;
}

void dbgToggle() {
    LATC7 = !LATC7;
}

volatile uint16 timer;

// global interrupt routine
void interrupt isr(void) {
  if(TMR0IF) {
    TMR0IF = 0;
    timer++;
    if(timer == 0) {
      volatile int x = 0;
    }
  }
}

void delayMs(uint16 ms) {
  uint16 start = timer;
  while (timer != (start + (ms * 1000)/clkPeriod));
}

uint16 getRomWord(uint16 addr) {
    NVMCON1bits.NVMREGS = 0;
    NVMADRL = addr & 0xff;
    NVMADRH = addr >> 8;
    NVMCON1bits.RD = 1;
    return  ((uint16) NVMDATH << 8) | NVMDATL;   
}
