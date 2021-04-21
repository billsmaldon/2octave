/*  The code of encoder.c and encoder.h is a derivative work of the code from
    Buxtronix, which is licensed GPL v3. This code therefore is also licensed
    under the terms of the GNU Public License, verison 3.
    https://github.com/buxtronix/arduino/tree/master/libraries/Rotary
*/ 

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

#ifndef ENCODER_H_INCLUDED
#define ENCODER_H_INCLUDED

#include <xc.h>
#include "menu.h"

void encoderInputsBuxton(void);     //read encoder bits
void processEncoderBuxton(void);    //rotary encoder pins are read in ISR, processed here

//variables for encoder input
unsigned char encoder_state_now = 0x00;     //char state of encoder pins "now"
unsigned char encoder_state_last = 0x00;    //char state of encoder pins "last"

//encoder variables
unsigned char state = 0x00;                 //start encoder at state "0x00"
unsigned char encoder_direction = 0x00;     //start encoder direction at "0x00"

//bool that stores encoder click
__bit encoder_click;                        

// Values returned by 'process'
#define DIR_NONE 0x00 // No complete step yet.
#define DIR_CW 0x10 // Clockwise step.
#define DIR_CCW 0x20 // Anti-clockwise step.

// Use the full-step state table (emits a code at 00 only)
#define R_START 0x0
#define R_CW_FINAL 0x1
#define R_CW_BEGIN 0x2
#define R_CW_NEXT 0x3
#define R_CCW_BEGIN 0x4
#define R_CCW_FINAL 0x5
#define R_CCW_NEXT 0x6

const unsigned char ttable[7][4] = {
  // R_START
  {R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},
  // R_CW_FINAL
  {R_CW_NEXT,  R_START,     R_CW_FINAL,  R_START | DIR_CW},
  // R_CW_BEGIN
  {R_CW_NEXT,  R_CW_BEGIN,  R_START,     R_START},
  // R_CW_NEXT
  {R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START},
  // R_CCW_BEGIN
  {R_CCW_NEXT, R_START,     R_CCW_BEGIN, R_START},
  // R_CCW_FINAL
  {R_CCW_NEXT, R_CCW_FINAL, R_START,     R_START | DIR_CCW},
  // R_CCW_NEXT
  {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START},
};

#endif