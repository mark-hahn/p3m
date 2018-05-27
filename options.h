#ifndef OPTIONS_H
#define	OPTIONS_H

#include "util.h"

// temporary until put in settings
#define optHoldTime 2000 // ms

#define RESET_OPTIONS     false
#define DONT_SAVE_OPTIONS false

#define OPTION_ROM_ADDR    0x1000
#define OPTION_ROM_ADDR_HI 0x10
#define OPTION_ROM_ADDR_LO 0x00

// any changes MUST be appended since def stored in existing units
#define firstOptionCode 200
enum optionCodes {
    magicOption = firstOptionCode,
    pasteClickOption,  // microns
    pasteHoldOption,   // microns/sec
    lastOptionCode
};
#define optionsCount (lastOptionCode - firstOptionCode)

// IMPORTANT: make sure linker options reserves 32 words
//   --ROM=default,-1000-1020

union valFld {
  uint8  data[optionsCount*2];
  uint16 words[optionsCount];
  struct vfs {
      uint16 magic;
      uint16 pasteClick;
      uint16 pasteHold;
  } val;
};

extern union valFld option;

void loadOptions();
void optValDown(uint8 optCode);
void optValUp(uint8 optCode);
void saveOptions();
char *optionStr(uint8 optCode);

#endif	/* OPTIONS_H */

