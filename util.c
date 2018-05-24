
#include <xc.h>
#include "util.h"
#include "smot.h"
#include "bmotor.h"
#include "lcd.h"
#include "exp-panel.h"

volatile uint8 DBG;

void utilInit() {
  T0ASYNC             = 0;   // sync clock
  T016BIT             = 0;   // 8-bit counter
  T0CON1bits.T0CS     = 5;   // src clk is MFINTOSC (500 khz)
  T0CON1bits.T0CKPS   = 0;   // prescaler  is 1:1 (2 usecs)
  TMR0H               = 7;   // wraps at count 8 (16 usecs)
  TMR0IF              = 0;   // int flag
  T0EN                = 1;   // enable timer0
  TMR0IE              = 1;   // enable timer int
  PEIE                = 1;   // enable peripheral ints
  GIE                 = 1;   // enable all ints
}

volatile uint16 time;

uint16 timer() {
  GIE = 0;
  uint16 tim = time;
  GIE = 1;
  return time;
}

void delay128Usecs(uint16 ticks) {
  uint16 start = timer();
  while (timer() != (start + ticks));
}

void delayMs(uint16 ms) {
  for(uint16 i=0; i < ms; i++)
    delay128Usecs(8);
}

// global interrupt routine
uint8 subTime;
uint8 motorIdx;

void globalInt() {
  if(++subTime == 8) {
    subTime = 0;
    time++; // 128 usec
  }
  if(motorIdx < 3) 
    smotInt(motorIdx); // 96 usec
  else
    bmotInt(motorIdx-3); // 96 usec
  if(++motorIdx == 6)
    motorIdx = 0;
  
  TMR0IF = 0; // only int source
}

uint16 getRomWord(uint16 addr) {
    NVMCON1bits.NVMREGS = 0;
    NVMADRL = addr & 0xff;
    NVMADRH = addr >> 8;
    NVMCON1bits.RD = 1;
    return  ((uint16) NVMDATH << 8) | NVMDATL;   
}

void beep(uint8 count) {
//  for(int i=0; i<count; i++) {
//    expWriteA(~buzzMask);
//    delayMs(beepMs);
//    expWriteA(buzzMask);
//    delayMs(100);
//  };
//  delayMs(400);
}

