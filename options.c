
#include <xc.h>
#include "util.h"
#include "options.h"

//#define MAGIC_WORD 0x10df

void flash_memory_erase();
void saveOptions();

union valFld option;

void loadOptions() {
  uint16 addr = OPTION_ROM_ADDR;
  uint16 magic = getRomWord(addr);
  if(magic != 0x16df) { // empty option data
    option.val.magic = 0x16df;
    option.val.pasteClick = 1000; // microns
    option.val.pasteHold  = 1000; // microns/sec
    saveOptions();
  } else {
    for(uint8 wordIdx = 0; wordIdx < optionsCount; wordIdx++)
      option.words[wordIdx] = getRomWord(OPTION_ROM_ADDR + wordIdx);
  }
}

uint16 optValChoices[optionsCount][5] = {
  {500, 1000, 1500, 2000, 0}, // pasteClickOption
  {500, 1000, 1500, 2000, 0}, // pasteHoldOption
};

void optValDown(uint8 optCode) {
  uint8 optCodeIdx = optCode-firstOptionCode;
  for(uint8 optValIdx = 1; optValChoices[optCodeIdx-1][optValIdx]; optValIdx++) {
    if(option.words[optCodeIdx] == optValChoices[optCodeIdx-1][optValIdx]) {
      option.words[optCodeIdx] = optValChoices[optCodeIdx-1][optValIdx-1];
      return;
    }
  }
}
void optValUp(uint8 optCode) {
  uint8 optCodeIdx = optCode-firstOptionCode;
  for(uint8 optValIdx = 0; optValChoices[optCodeIdx-1][optValIdx]; optValIdx++) {
    if(option.words[optCodeIdx] == optValChoices[optCodeIdx-1][optValIdx]) {
      uint16 next = optValChoices[optCodeIdx-1][optValIdx+1];
      if(next) option.words[optCodeIdx] = next;
      return;
    }
  }  
}

char  glblOptStr[32];
char *glblOptStrPtr;

void addStr(const char *str) {
  for(; *str; str++) {
    *glblOptStrPtr = *str;
    glblOptStrPtr++;
  }
}

void addInt(uint8 n) {
  char digStr[] = {0,0};
  if(n==0) {
    addStr("0");
    return;
  }
  if(n >= 100) {
    *digStr = (48 +        n / 100); addStr(digStr);
    *digStr = (48 + (n % 100)/  10); addStr(digStr);
    *digStr = (48 +  n %  10);       addStr(digStr);
  } else if( n >= 10) {
    *digStr = (48 + n / 10); addStr(digStr);
    *digStr = (48 + n % 10); addStr(digStr);
  } else {
    *digStr = (48 + n); addStr(digStr);
  }
}

void addNum(uint16 num){
  uint8 man  = num / 1000;
  uint8 frac = (num-man*1000)/100;
  addInt(man);
  addStr(".");
  addInt(frac);
}

char *optionDistStr(uint16 microns) {
  addNum(microns);
  addStr(" mm");
  *glblOptStrPtr = 0;
  return glblOptStr;
}

char *optionRateStr(uint16 micronsPerSec) {
  addNum(micronsPerSec);
  addStr(" mm/sec");
  *glblOptStrPtr = 0;
  return glblOptStr;
}

char *optionStr(uint8 optCode) {
  glblOptStrPtr = glblOptStr;
  addStr("  = ");
  switch (optCode) {
    case pasteClickOption: return optionDistStr(option.val.pasteClick);
    case pasteHoldOption:  return optionRateStr(option.val.pasteHold);
  }
  return (char *) "error"; 
}

void flash_memory_erase () {
  NVMADRL = OPTION_ROM_ADDR_LO;
  NVMADRH = OPTION_ROM_ADDR_HI;
  NVMCON1 = 0x94; 	// access FLASH memory, wren=1, FREE specifies erase 
  NVMCON2 = 0x55;
  NVMCON2 = 0xaa;
  NVMCON1bits.WR = 1;       // Start the write
  // processor freezes here until erase finished
  WREN = 0;  // disallow program/erase		
}

void saveOptions () {
  if(DONT_SAVE_OPTIONS) return;
  flash_memory_erase();
  char wordIdx;
  uint16 wordAddress = OPTION_ROM_ADDR;
  NVMCON1 = 0x24; // LWLO=1 => don't flash yet, WREN=1 => allow write
  for (wordIdx=0; wordIdx < optionsCount; wordIdx++)  {
    NVMADRL = (wordAddress & 0xff);	// load address low byte
    NVMADRH = (wordAddress >> 8   );	// load word address high byte
    if(wordIdx == optionsCount-1)
      LWLO = 0; // do actual flash this time
    NVMDATL = option.data[wordIdx*2];
    NVMDATH = option.data[wordIdx*2+1];
    NVMCON2 = 0x55;
    NVMCON2 = 0xaa;
    WR = 1;       // Start the write
    wordAddress++;
  }	
  // processor freezes here until erase finished
  WREN = 0;  // disallow program/erase
}

void optionsTest() {
  
}