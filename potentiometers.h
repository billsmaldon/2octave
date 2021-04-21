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

#ifndef POTENTIOMETERS_INCLUDED
#define	POTENTIOMETERS_INCLUDED

#include <xc.h>
#include "midi.h"
#include "segment.h"
#include "adc.h"

//#define NUM_ANALOG 7        //for breadboard
#define NUM_ANALOG 16     //for PCB

//arduino function used to map potentiometers
long map(long x, long in_min, long in_max, long out_min, long out_max);
//gets potentiometer inputs and smooths them with filter algorithm
//also applies hysteresis (for less fluctuations) and bit-shifts the samples (for 7 bit samples or 14 bit samples)
void readPotentiometers(void);
//transmits midi control changes (send control change)
void processPotentiometers(unsigned char i);

float ema_alpha = 0.10; //alpha (for potentiometer smoothing)
int HYST_VAL = 8;       //hysteresis on potentiometer input (for less fluctuations)

 //potentiometer sample arrays below --- important to initialize all arrays to "{0}" !!!

int potentiometer_raw[NUM_ANALOG] = {0};    //array of raw potentiometer inputs (10 bits)
signed int ema_sum[NUM_ANALOG] = {0};       //ema smoothed value - must use a signed int!

//smoothed and bit-shifted potentiometers:
int potentiometer_filtered_now[NUM_ANALOG] = {0};   //filtered potentiometer values (now)
int potentiometer_filtered_last[NUM_ANALOG] = {0};  //filtered potentiometer values (last)

//POTENTIOMETER STRUCT:
typedef struct Potentiometers {
    unsigned controller_resolution : 1; // HIGH OR LOW resolution input reading
    signed char controller_number;    // controlChange number associated with the potentiometer
    signed char controller_number_two_byte;//char controller_name[5];            // a string to display for the selected potentiometer
} potentiometer_type;

//one bit that selects resolution, for 7 bit/14 bit mode
#define LO_RES 0
#define HI_RES 1
__bit POT_MODE;

//resolution, a 7 bit controller number, a 14 bit controller number
#define POT1 {LO_RES, knob_1, knob_1_MSB}
#define POT2 {LO_RES, knob_2, knob_2_MSB} 
#define POT3 {LO_RES, knob_3, knob_3_MSB}
#define POT4 {LO_RES, knob_4, knob_4_MSB}
#define POT5 {LO_RES, knob_5, knob_5_MSB} 
#define POT6 {LO_RES, knob_6, knob_6_MSB}
#define POT7 {LO_RES, knob_7, knob_7_MSB}
#define SPOT1 {LO_RES, slider_1, slider_1_MSB}
#define SPOT2 {LO_RES, slider_2, slider_2_MSB}
#define SPOT3 {LO_RES, slider_3, slider_3_MSB}
#define SPOT4 {LO_RES, slider_4, slider_4_MSB}
#define SPOT5 {LO_RES, slider_5, slider_5_MSB}
#define SPOT6 {LO_RES, slider_6, slider_6_MSB}
#define SPOT7 {LO_RES, slider_7, slider_7_MSB}
#define JXPOT {LO_RES, modulation_wheel_controller_number, modulation_wheel_controller_number}
#define JYPOT {LO_RES, pitch_bend_controller_number, pitch_bend_controller_number}

//initialize array of potentiometer structs (for potentiometer inputs):

//breadboard (7 potentiometers)
//potentiometer_type inputPotsArray[NUM_ANALOG] = {POT1,POT2,POT3,POT4,SPOT1,JXPOT,JYPOT};

//PCB (16 potentiometers) --- JXPOT and JYPOT are in reverse axis on the PCB. switched the order --- JYPOT,JXPOT
potentiometer_type inputPotsArray[NUM_ANALOG] = {POT1,POT2,POT3,POT4,POT5,POT6,POT7,SPOT1,SPOT2,SPOT3,SPOT4,SPOT5,SPOT6,SPOT7,JYPOT,JXPOT};

#endif

