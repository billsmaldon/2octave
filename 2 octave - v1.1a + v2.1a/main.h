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

#ifndef MAIN_INCLUDED
#define	MAIN_INCLUDED

#define _XTAL_FREQ 20000000 //20 MHz

//compile for board version number
//#define MIDI_V_1_0_BOARD    //for v1.0 boards
#define MIDI_V_2_0_BOARD  //for v2.0, v2.1 boards

//set the encoder polarity
#define EBAY_ENCODER        //CW is increase
//#define DIGIKEY_ENCODER   //CCW is increase

//number of digital inputs, number of analog inputs
#define NUM_DIGITAL 40  //set to 40 (for PCB)
#define NUM_ANALOG 16   //set to 16 (for PCB)

//comment this in/out to test coarse/fine switching time
//#define POTENTIOMETER_TEST_MODE

//delay switching from 'fine' back to 'coarse' (potentiometer inputs)
#define number_of_repeats 1024          //in clock cycles
#define coarse_fine_delay_ms 125        //in milliseconds
//unsigned long number_of_interrupts = (int) coarse_fine_delay_ms / 2.5 ;     //in TIMER2 interrupts (2.5 mS)
unsigned long number_of_interrupts = coarse_fine_delay_ms;                    //in TIMER1 interrupts (1.0 mS)
unsigned long count_ISR;                //count TIMER2 or TIMER1 interrupts

__bit ARPEGGIO_IS_PLAYING;

//SOFTWARE DEBOUNCE DELAYS(for pushbutton input)
#define switch_debounce_ms 10
#define encoder_click_debounce_ms 10

void analogInputs(void); //added this!
void digitalInputs(void);
void processEncoderBuxton(void);

#endif