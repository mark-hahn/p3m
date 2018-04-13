
#include <xc.h>
#include "util.h"
#include "ints.h"
#include "exp.h"

bool intPinChg = false;

void initInts() {
    // global ints on
    IOCIE =  1; // Interrupt on pin change (exp int pin and fault pin)
    PEIE  =  1; // Peripheral Interrupt Enable
    GIE   =  1; // Global Interrupt Enable
}

// global interrupt routine
void interrupt isr(void) {
  // sw pin int
  if(intPinIOCF) {
    intPinIOCF = 0;
    intPinChg = true;
  }
}
