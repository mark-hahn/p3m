
#include "lights.h"
#include "util.h"
#include "i2c.h"


#define lgtsI2cAddr   0x41
#define lgtsDataLat   0x01
#define lgtsConfigCmd 0x03

void lgtsInit() {
  i2cSendTwoBytes(lgtsI2cAddr, lgtsConfigCmd, 0); // all outputs
}

void lgtsSet(uint8 val){
  i2cSendTwoBytes(lgtsI2cAddr, lgtsDataCmd, ~val);
}

void lgtsDemo() {
  lgtsSet(0x0f);
  delayMs(1000);
  lgtsSet(0x00);
  delayMs(1000);
  for(uint8 i=0; i<4; i++) {
    lgtsSet(0x01 << i);
    delayMs(300);
  }
  lgtsSet(0x00);
  delayMs(1000);
}