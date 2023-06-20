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

#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include "midi.h"
#include "theory.h"
#include "segment.h"

void processKeyboard(void);         //select keyboard mode

//keyboard input
void keyboard_all_note(void);
void keyboard_eight_note(void);

//more efficient way of keyboard input
void keyboard_all_note_efficient(void);
void keyboard_eight_note_efficient(void);
void keyboard_sharps_only_efficient(void);

__bit ON_OFF;

void playTriad(unsigned char pitch);
void playSeventh(unsigned char pitch);
void playThisNote(unsigned char pitch);
void playThisNote8(unsigned char pitch, unsigned char index);
void playThisNotePentatonic(unsigned char pitch, unsigned char index);

void playDiatonicTriadMajor(unsigned char pitch, unsigned char index);
void playDiatonicTriadMinor(unsigned char pitch, unsigned char index);
void playDiatonicSeventhMajor(unsigned char pitch, unsigned char index);
void playDiatonicSeventhMinor(unsigned char pitch, unsigned char index);

//keyboard pushbuttons:
#define BUTTON_0  0x00000001
#define BUTTON_1  0x00000002
#define BUTTON_2  0x00000004
#define BUTTON_3  0x00000008

#define BUTTON_4  0x00000010
#define BUTTON_5  0x00000020
#define BUTTON_6  0x00000040
#define BUTTON_7  0x00000080
    
#define BUTTON_8  0x00000100
#define BUTTON_9  0x00000200
#define BUTTON_10 0x00000400
#define BUTTON_11 0x00000800
            
#define BUTTON_12 0x00001000
#define BUTTON_13 0x00002000
#define BUTTON_14 0x00004000
#define BUTTON_15 0x00008000 
            
#define BUTTON_16 0x00010000
#define BUTTON_17 0x00020000
#define BUTTON_18 0x00040000
#define BUTTON_19 0x00080000

#define BUTTON_20 0x00100000
#define BUTTON_21 0x00200000
#define BUTTON_22 0x00400000
#define BUTTON_23 0x00800000
    
#define BUTTON_24 0x01000000

//octave +/- and shift buttons:
#define BUTTON_25 0x02000000    //octave down
#define BUTTON_26 0x04000000    //octave up
#define BUTTON_27 0x08000000    //shift

//these buttons not implemented:
//#define BUTTON_28 0x10000000
//#define BUTTON_29 0x20000000
//#define BUTTON_30 0x40000000
//#define BUTTON_31 0x80000000

//for extra 8 bits input (drum buttons)
#define DRUM_BUTTON_0 0x01
#define DRUM_BUTTON_1 0x02
#define DRUM_BUTTON_2 0x04
#define DRUM_BUTTON_3 0x08
            
#define DRUM_BUTTON_4 0x10
#define DRUM_BUTTON_5 0x20
#define DRUM_BUTTON_6 0x40
#define DRUM_BUTTON_7 0x80

//variables for pushbutton input

//variable for keyboard + octave
unsigned long long button_state_now = 0x00000000; //support for up to 32 bits of digital inputs
unsigned long long button_state_last = 0x00000000; //last button press
//variable for drum buttons
unsigned char drum_button_state_now = 0x00;
unsigned char drum_button_state_last = 0x00;

//bit-field for keyboard inputs
typedef struct{
   unsigned SW1  :1;
   unsigned SW2  :1;
   unsigned SW3  :1;
   unsigned SW4  :1;
   unsigned SW5  :1;
   unsigned SW6  :1;
   unsigned SW7  :1;
   unsigned SW8  :1;
   unsigned SW9  :1;
   unsigned SW10  :1;
   unsigned SW11  :1;
   unsigned SW12  :1;
   unsigned SW13  :1;
   unsigned SW14  :1;
   unsigned SW15  :1;
   unsigned SW16  :1;
   unsigned SW17  :1;
   unsigned SW18  :1;
   unsigned SW19  :1;
   unsigned SW20  :1;
   unsigned SW21  :1;
   unsigned SW22  :1;
   unsigned SW23  :1;
   unsigned SW24  :1;
   unsigned SW25  :1;
}new_note_keyboard;

//bit-field for drum inputs
typedef struct{
   unsigned SW1  :1;
   unsigned SW2  :1;
   unsigned SW3  :1;
   unsigned SW4  :1;
   unsigned SW5  :1;
   unsigned SW6  :1;
   unsigned SW7  :1;
   unsigned SW8  :1;
}new_note_drum;


//KEEPS TRACK OF NOTE ON/NOTE OFF
new_note_keyboard keyboard = {0};
new_note_drum drum = {0};

#endif