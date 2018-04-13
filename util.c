
#include <xc.h>
#include "util.h"

void utilInit() {
    LATC7  = 0;
    TRISC7 = 0; // fault line used as debug pin
    
    T0ASYNC             = 0;   // sync clock
    T016BIT             = 1;   // 16-bit counter
    T0CON1bits.T0CS     = 5;   // src clk is MFINTOSC (500 kHz)
    T0CON1bits.T0CKPS   = 5;   // prescaler  is 1:32 (15.625 khz, 64 usecs
    T0CON1bits.T0PS     = 0;   // postscaler is 1:1
    
    TMR0IF = 0;
    T0EN   = 1;   // enable timer0
    TMR0IE = 1;   // enable timer ints
    PEIE   = 1;   // Peripheral Interrupt Enable
    GIE    = 1;   // Global Interrupt Enable  
}

void dbg() {
    LATC7 = 1;
    int x=1;
    LATC7 = 0;
}

volatile uint16 timer;

// global interrupt routine
void interrupt isr(void) {
  if(TMR0IF) {
    TMR0IF = 0;
    uint8 timerLow = TMR0L;
    timer = TMR0H * 0X100 | timerLow;
    volatile int x = 0;
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
