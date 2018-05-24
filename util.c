
#include <xc.h>
#include "util.h"
#include "smot.h"
#include "bmotor.h"
#include "lcd.h"
#include "exp-panel.h"

volatile uint8 DBG;

void utilInit() {
  T0ASYNC             =  0;   // sync clock
  T016BIT             =  0;   // 8-bit counter
  T0CON1bits.T0CS     =  5;   // src clk is MFINTOSC (500 khz)
  T0CON1bits.T0CKPS   =  0;   // prescaler  is 1:1 ( 2 usecs)
  TMR0H               = 41;   // wraps at count 42 (84 usecs, 11.9 khz)
  TMR0IF              =  0;   // int flag
  T0EN                =  1;   // enable timer0
  TMR0IE              =  1;   // enable timer int
  PEIE                =  1;   // enable peripheral ints
  GIE                 =  1;   // enable all ints
}

volatile uint16 time;

// each tick is 1 ms
uint16 timer() {
  GIE = 0;
  uint16 tim = time;
  GIE = 1;
  return time;
}

void delayMs(uint16 ms) {
  uint16 start = timer();
  while (timer() != (start + ms)) NOP();
}

// global interrupt routine
uint8 subTime;
uint8 motorIdx;

void interrupt globalInt() {
  faultLAT = 1;

  if(++subTime == 12) {
    subTime = 0;
    time++; // 1 ms
  }
  if(motorIdx < 3) 
    smotInt(motorIdx);   // each motor called every 500 us
  else
    bmotInt(motorIdx-3); // each motor called every 500 us
  if(++motorIdx == 6)
    motorIdx = 0;
  
  TMR0IF = 0; // only int source
  
  faultLAT = 0;
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

