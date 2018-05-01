
#include "util.h"
#include "smot.h"


// -------- phases ----------
// schematic     3  2  1  0
// pin idx       0  1  2  3
// Color        Bl Pi Ye Or
//              {1, 1, 0, 0},
//              {0, 1, 1, 0},
//              {0, 0, 1, 1},
//              {1, 0, 0, 1}

uint8 smotPortMask[3] = {0xf0, 0x0f, 0x0f};
uint8 smotPortValue[3][4] = { // motor, phase
    {0x30, 0x60, 0xc0, 0x90},
    {0x03, 0x06, 0x0c, 0x09},
    {0x03, 0x06, 0x0c, 0x09}
};

uint8 smotCurPhaseByMot[3];

void smotInit() {
    for(uint8 motor=0; motor < 3; motor++) {
        smotCurPhaseByMot[motor] = 0;
    }        
    smoteLat = (smoteLat & ~smotPortMask[smote]) | 
                            smotPortValue[smote][0];
    smotpLat = (smotpLat & ~smotPortMask[smotp]) | 
                            smotPortValue[smotp][0];
    smotfLat = (smotfLat & ~smotPortMask[smotf]) | 
                            smotPortValue[smotf][0];
    for(uint8 motor=0; motor < 3; motor++) {
       smotOnOff(motor, 0);
    }        
}

void smotOnOff(uint8 motor, bool on) {
    uint8 tris;
     switch (motor) {
        case smote: tris = smoteTris; break;
        case smotp: tris = smotpTris; break;
        case smotf: tris = smotfTris; break;
    }
    tris = (tris & ~smotPortMask[motor]);
    if(!on) tris = tris | smotPortMask[motor];
    switch (motor) {
        case smote: smoteTris = tris; break;
        case smotp: smotpTris = tris; break;
        case smotf: smotfTris = tris; break;
    }
}

void smotStep(uint8 motor, int dir){
    uint8 phase = smotCurPhaseByMot[motor] = 
                 (smotCurPhaseByMot[motor] + dir) & 3;
    uint8 portVal;
    switch (motor) {
        case smote: portVal = smoteLat; break;
        case smotp: portVal = smotpLat; break;
        case smotf: portVal = smotfLat; break;
    }
    portVal = (portVal & ~smotPortMask[motor]) | 
                          smotPortValue[motor][phase];
    switch (motor) {
        case smote: smoteLat = portVal; break;
        case smotp: smotpLat = portVal; break;
        case smotf: smotfLat = portVal; break;
    }
}

// 800 pps max
void smotTest(uint8 motor, uint16 pps, int dir){
    smotOnOff(smote, 1);
    smotOnOff(smotp, 1);
    smotOnOff(smotf, 1);
    uint16 tgtSpeed = 4000/pps;
    uint16 speed = 100; // start at 40 pps then accelerate
    while(1) {
        if(speed > tgtSpeed) speed--;
        for(uint16 i=0; i < speed; i++) {
            for(uint8 j=0; j<100; j++) {}
        }
        smotStep(smote, dir);
        smotStep(smotp, dir);
        smotStep(smotf, dir);
    }
}