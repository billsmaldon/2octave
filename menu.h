/* This file is part of 2octave.

    2octave is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    2octave is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with 2octave.  If not, see <https://www.gnu.org/licenses/>.

 */

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <xc.h>
#include "lcd.h"
#include "potentiometers.h"
#include "encoder.h"

//#define NUM_ANALOG 7        //for breadboard
#define NUM_ANALOG 16     //for PCB

//misc. function prototypes
void initializeMenuArray(void);         //fills in addresses of display strings
void clear_row1(void);                  //clears row 1 of LCD and sets cursor to 1,1
void clear_row2(void);                  //clears row 2 of LCD and sets cursor to 2,1
void int2string(signed char number);    //converts a signed char to a string
void setControllerResolution(void);     //sets resolution of continuous controllers
void setControllerNumbers(unsigned char array_index);   //sets controller numbers
void exitFunction(void);                //exits most functions
void exitSave(void);                    //exits save function
void exitLoad(void);                    //exits load function
void eepromExit(void);                  //exits eeprom function

//menu function prototypes
void menu_lcd(void);                    // !!! main menu function !!!
void Function_A_1(void);                //set MODES
void Function_A_2(void);                //set TRIADS
void Function_A_3(void);                //set SEVENTHS
void Function_A(void);                  //KEYBOARD MODE MENU
void Function_B(void);                  //set TRANSPOSE MODE
void Function_C_1(void);                //set DRUMS CC TYPE
void Function_C_2(void);                //set DRUMS NOTE NUMBER
void Function_C_3(void);                //set DRUMS CC NUMBER               
void Function_C(void);                  //DRUM MENU
void Function_D_1(void);                //set POTENTIOMETER RESOLUTION
void Function_D_2(void);                //set POTENTIOMETER CC NUMBER
void Function_D_3(void);                //set SLIDEPOTS CC NUMBER
void Function_D_4(void);                //set JOYSTICK CC NUMBER
void Function_D(void);                  //POTENTIOMETER MENU
void Function_E_1(void);                //set MAIN CHANNEL
void Function_E_2(void);                //set DRUM CHANNEL
void Function_E(void);                  //MIDI CHANNEL MENU
void Function_F(void);                  //PROGRAM CHANGE MENU
void Function_G_1 (void);               //save to EEPROM
void Function_G_2 (void);               //load from EEPROM
void Function_G_3 (void);               //restore defaults
void Function_G(void);                  //EEPROM MENU

char string2display[5];  //used by int2string(), to print numbers on LCD

//variable to update the LCD only once
__bit lcd_print_once;

//which_screen is selected (LCD), for update by rotary encoder
enum {
    BLANK,                  // no screen is selected
    SEG,                    // 7 segment is selected (unused)
    MAIN_MENU,              // main LCD menu
    KEYBOARD_MENU,          // keyboard sub-menu
    TRANSPOSE_MENU,         // transpose sub-menu
    DRUM_MENU,              // drum sub-menu
    POTENTIOMETER_MENU,     // potentiometer sub-menu
    MIDI_CHANNEL_MENU,      // midi channel sub-menu
    PROGRAM_CHANGE_MENU,    // program change sub-menu
    MODES_MENU,             // modes sub-menu
    TRIADS_MENU,            // triads sub-menu
    SEVENTHS_MENU,          // sevenths sub-menu
    DRUMS_CC_TYPE_MENU,     // drums cc type sub-menu
    DRUMS_NN_MENU,          // drums nn sub-menu
    DRUMS_CC_MENU,          // drums cc sub-menu
    POTS_RES_MENU,          // potentiometer resolution sub-menu
    POTS_CC_MENU,           // potentiometer cc sub-menu
    SLIDEPOTS_CC_MENU,      // slide potentiometer cc sub-menu
    JOYSTICK_CC_MENU,       // joystick potentiometer cc sub-menu
    MAIN_CH_MENU,           // main channel sub-menu
    DRUM_CH_MENU,           // drum channel sub-menu
    EEPROM_MENU,            // eeprom save/load sub-menu
    SAVES_MENU              // eeprom slot number sub-menu
};

//default to MAIN_MENU on boot-up
unsigned char which_screen = MAIN_MENU;

//      *** MENU ITEMS STRUCT ***      //
typedef struct menuItem {
    unsigned char number;       //number of items in menu/sub-menu
    unsigned char address;      //address of the start of the strings
    unsigned char selector;     //selector (is ++/-- by the rotary encoder)
} menu_type;

//NUMBER OF ITEMS IN MENU/SUB_MENU - initializes menuItem.number
#define M1 {7}      //MAIN_MENU
#define M2 {10}     //KEYBOARD_MENU
#define M3 {7}      //MODE_MENU
#define M4 {4}      //TRIAD_MENU
#define M5 {5}      //SEVENTH_MENU
#define M6 {2}      //TRANSPOSE_MENU
#define M7 {5}      //DRUM_MODE_MENU
#define M8 {2}      //DRUM_CC_TYPE_MENU
#define M9 {8}      //DRUM_NOTE_NUMBER_MENU
#define M10 {8}     //DRUM_CC_NUMBER_MENU
#define M11 {4}     //POTS_MENU
#define M12 {2}     //POTS_RESOLUTION_MENU
#define M13 {7}     //POTS_CC_MENU
#define M14 {7}     //SLIDEPOTS_CC_MENU
#define M15 {2}     //JOYSTICK_CC_MENU
#define M16 {2}     //MIDI_CHANNEL_MENU
#define M17 {4}     //EEPROM_MENU
#define M18 {5}     //SAVES_MENU

//array of structs (used to automatically calculate string addresses)
//put this in the .c in initializeMenuArray() ?
menu_type menuArray[] = {M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11, M12, M13, M14, M15, M16, M17, M18};

//inidividual structs for every menu item (these structs are actually used in the code)
menu_type mainMenu;
menu_type keyboardMenu;
menu_type modeMenu;
menu_type triadMenu;
menu_type seventhMenu;
menu_type transposeMenu;
menu_type drumMenu;
menu_type drumCCTypeMenu;
menu_type drumNNMenu;
menu_type drumCCMenu;
menu_type potsMenu;
menu_type potsResoMenu;
menu_type potsCCMenu;
menu_type slidepotsCCMenu;
menu_type joystickCCMenu;
menu_type midiChannelMenu;
menu_type programChangeMenu;
menu_type mainChannelMenu;
menu_type drumChannelMenu;
menu_type eepromMenu;
menu_type savesMenu;



#endif