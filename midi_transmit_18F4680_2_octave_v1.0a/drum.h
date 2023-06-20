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

#ifndef DRUM_H_INCLUDED
#define DRUM_H_INCLUDED

#include "midi.h"
#include "keyboard.h"

//drum channel note on/note off/control change
void processDrumpad(void);

//pitch of drum pads 1-8
unsigned char DRUM_NOTE[8] = {DRUM_0,DRUM_1,DRUM_2,DRUM_3,
                              DRUM_4,DRUM_5,DRUM_6,DRUM_7};

//controller number of drum pads 1-8
unsigned char DRUM_CC[8] = {button_1,
                            button_2,
                            button_3,
                            button_4,
                            button_5,
                            button_6,
                            button_7,
                            button_8};

//bit-field for drum buttons in TOGGLE MODE
typedef struct{
   unsigned T1  :1;
   unsigned T2  :1;
   unsigned T3  :1;
   unsigned T4  :1;
   unsigned T5  :1;
   unsigned T6  :1;
   unsigned T7  :1;
   unsigned T8  :1;   
   
}toggle_bools;

toggle_bools toggle_state;  //bit-field to toggle a drum button

//drum button control change ON/OFF values
#define DRUM_CC_ON 127
#define DRUM_CC_OFF 0

//drum button is note or control change
#define NOTE 0
#define CONTROL 1
__bit DRUM_MODE;

//drum button control change is trigger or toggle
#define TRIGGER 0
#define TOGGLE 1
__bit CONTROL_MODE;

#endif