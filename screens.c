
#include "screens.h"
#include "lcd.h"
#include "font708.h"
#include "font813.h"

// icons 
//  \x80\x81 square button
//  \x82     empty rocker
//  \x83     top rocker
//  \x84     bot rocker
//  \x85     both rocker
//  \x86 up arrow
//  \x87 dn arrow

const char blankStr[]        = "";
const char pressSquareStr[]  = "           (Press\x80\x81)";
const char menuHelpContStr[] = "MENU HELP cont.";
const char lightsStr[]       = "\x80\x81+ \x83\x82 Lights";  
const char focusStr[]        = "\x80\x81+ \x84\x82 Focus";   
const char zoomStr[]         = "\x80\x81+ \x82\x85 Zoom";    

const char *menuLines[6][6] = {
   {"MAIN MENU",                    // mainMenu
    ">Paste",                      
    ">Pick / Place",               
    ">Inspect",                    
    ">Settings",                   
    "  (Press\x80\x81 for help)"}, 

    {"SETTINGS MENU",               // settingsMenu
    ">Button Press",               
    ">Rotate",                     
    ">Pinch",                      
    ">Paste",
    blankStr},
    
   {"MENU HELP",                    // menuHelp
    "The symbol\x80\x81 is the",   
    "leftmost button.",            
    "It takes you back",           
    "to the MAIN MENU.",           
    pressSquareStr},  
    
   {menuHelpContStr,                 // menuHelp2
    "The pair \x82\x82 are on",    
    "the right. \x85 means",       
    "press \x86 or \x87 and",      
    "\x83 means just \x86.",       
    pressSquareStr},  
    
    {menuHelpContStr,                // menuHelp3
    " --- Navigation ---",         
    "\x85\x82 Cursor Up/Down",     
    "\x82\x83 Back",               
    "\x82\x84 Select",             
    pressSquareStr}, 
    
    {"PASTE MODE",                   // pasteScreen
    "\x85\x82 Position Syringe",   
    "\x82\x85 Extrude/Retract",    
    lightsStr,
    focusStr,
    zoomStr}, 
//    
//    {"PICK/PLACE MODE",              // pickScreen
//    "\x85\x82 Rotate",             
//    "\x82\x85 Pinch/Unpinch",      
//    lightsStr,
//    focusStr,
//    zoomStr}, 
//            
//    {"INSPECTION MODE",             
//    "\x85\x82 Focus",              
//    "\x82\x85 Zoom",               
//    lightsStr,
//    focusStr,
//    "\x80\x81+ \x82\x85 Clear View"},
//            
//    "BUTTON PRESS",              
//    ">Time before hold action",  
//    ">Rotate",                   
//    ">Pinch",                    
//    ">Paste"                     
};

uint8 cursorLines[] = {
  4,  // mainMenu
  4   // settingsMenu
};

uint8 cursor, lastCursor, lastMenu;;

void initScreens() {
  cursor     = 1;
  lastCursor = 1;
  lastMenu   = 0;
}

void scrDrawMenu(uint8 menu, bool screenOnly, bool cursorOnly) {  
    lastMenu = menu;
    const char *line[6];
    for(uint8 i=0; i<6; i++)
      line[i] = menuLines[menu][i];
    if(!cursorOnly) {
      lcdClrPage(0);
      lcdClrPage(1);
      font813WriteStr(0,  0, 0, line[0]);
      font813WriteStr(1, -8, 0, line[0]);
    }
    if(!screenOnly) {
      if(!cursorOnly || cursor == 1 || lastCursor == 1) {
        lcdClrPage(2);
        font708WriteStr(2,  0, 0, line[1], cursor == 1);
      }
      if(!cursorOnly || cursor == 2 || lastCursor == 2) {
        lcdClrPage(3);
        font708WriteStr(3,  2, 0,  line[2], cursor == 2);
      }
      if(!cursorOnly || cursor == 2 || lastCursor == 2
                     || cursor == 3 || lastCursor == 3) {
        lcdClrPage(4);
        font708WriteStr(9, -6, 0, line[2], cursor == 2);
        font708WriteStr(4,  3, 0, line[3], cursor == 3);
      }
      if(!cursorOnly || cursor == 3 || lastCursor == 3
                     || cursor == 4 || lastCursor == 4) {
        lcdClrPage(5);
        font708WriteStr(9, -5, 0, line[3], cursor == 3);
        font708WriteStr(5,  6, 0, line[4], cursor == 4);
      }
      if(!cursorOnly || cursor == 4 || lastCursor == 4) {
        lcdClrPage(6);
        font708WriteStr(6, -2, 0, line[4], cursor == 4);
      }
      if(!cursorOnly || cursor == 5 || lastCursor == 5) {
        lcdClrPage(7);
        font708WriteStr(7,  0, 0, line[5], cursor == 5);
      }
    } else {
      font708WriteStr(2,  0, 0, line[1], false);
      font708WriteStr(3,  2, 0, line[2], false);
      font708WriteStr(9, -6, 0, line[2], false);
      font708WriteStr(4,  3, 0, line[3], false);
      font708WriteStr(9, -5, 0, line[3], false);
      font708WriteStr(5,  6, 0, line[4], false);
      font708WriteStr(6, -2, 0, line[4], false);
      font708WriteStr(7,  0, 0, line[5], false);
    }
}

void scrRedrawMenu(uint8 menu) {
  scrDrawMenu(menu, false, true);
}

void scrCursorUp() {
  if(cursor > 1) {
    cursor--;
    scrRedrawMenu(lastMenu);
    lastCursor = cursor;
  }
}

void scrCursorDown(uint8 menuIdx) {
  if(cursor < cursorLines[menuIdx]) {
    cursor++;
    scrRedrawMenu(lastMenu);
    lastCursor = cursor;
  }
}

