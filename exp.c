
#include "util.h"
#include "exp.h"
#include "i2c.h"

void expInit() {
    i2cSendTwoBytes(i2cExpAddr, IOCON,  0x80);  // bank bit = 1
    i2cSendTwoBytes(i2cExpAddr, IODIRA, 0xff);  // A all input
    i2cSendTwoBytes(i2cExpAddr, IODIRB, 0x00);  // B all output
}

uint8 expReadA() {
    return i2cReadByte(i2cExpAddr, GPIOA);
}

uint8 expReadB() {
    return i2cReadByte(i2cExpAddr, GPIOB);
}

void expWriteB(uint8 byt) {
    i2cSendTwoBytes(i2cExpAddr, GPIOB, byt);
}

void expTest() {
    i2cSendTwoBytes(i2cExpAddr, IODIRA, 0x00);  // all outputs
    while(1) {
        i2cSendTwoBytes(i2cExpAddr, GPIOA, 0x00);  // pins = 0
        i2cSendTwoBytes(i2cExpAddr, GPIOA, 0xff);  // pins = 1
        int x = i2cReadByte(i2cExpAddr, 0x05);  // IOCON in bank=1 mode
    }
}
