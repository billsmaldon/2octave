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

#ifndef ARPEGGIO_H_INCLUDED
#define ARPEGGIO_H_INCLUDED

#include "arpeggio.h"
#include "theory.h"
#include "midi.h"
#include "keyboard.h"
#include "menu.h"
#include "octave.h"

//calculate TIMER PRELOAD for PPQN/NOTE_LENGTH
unsigned short calculate_pulse_length(void);
//reset arpeggiator
void resetArpeggio(void);
//set up arpeggiator
void setupArpeggio(void);

//send noteOff()s on key press and release
void key_press_release_note_off(void);

//add notes to arpeggio
void add_notes_to_arpeggio(unsigned char pitch);
//delete notes from arpeggio
void delete_notes_from_arpeggio(unsigned char pitch);

void finish_arpeggio_setup(void);

//copy ARPEGGIO[] to ARPEGGIO_SORTED[], ARPEGGIO_RANDOM[]
void copy_array(void);
//sort pitches ASCENDING/DESCENDING
void sort_pitches(void);
//random pitches
void random_pitches(void);
//shuffle pitches
void random_pitches_non_repeating(void);

//function to play ALL arpeggio types
void playArpeggio(void);

//find array index to shift left at
signed char findArrayIndex(unsigned char pitch_of_key_release);
//shift the array of ARPEGGIO[] left
void shiftTheArray(unsigned char array_index);
//more efficient way of shifting ARPEGGIO[] (unfinished)
//void rotateArrayLeft (unsigned char n); //rotate array for arpeggio key release
void rotateArrayLeft (unsigned char array_index); //rotate array for arpeggio key release

/* enum for arpeggiator */
enum arpeggioType {
    UP,
    DOWN,
    UP_DOWN,
    DOWN_UP,
    RANDOM_NON_REPEATING,
    RANDOM,
    AS_PRESSED,
};

//sort arpeggio in ascending or descending order
#define ASCENDING 0
#define DESCENDING 1
__bit SORT_DIRECTION;

// MAIN ON/OFF for ARPEGGIO
__bit ARPEGGIO_ON;

//note lengths (in pulses)
enum NOTE_LENGTH {
    QUARTER             = 48,
    QUARTER_DOTTED      = 72,
    QUARTER_TRIPLET     = 32,
    EIGTH               = 24,
    EIGTH_DOTTED        = 36,
    EIGTH_TRIPLET       = 16,
    SIXTEENTH           = 12,
    SIXTEENTH_DOTTED    = 18,
    SIXTEENTH_TRIPLET   = 8,
    THIRTY2ND           = 6,
    THIRTY2ND_DOTTED    = 9,
    THIRTY2ND_TRIPLET   = 4,
};

//array of note lengths
unsigned char NOTE_LENGTH_PULSES_ARRAY[12] = 
{
    QUARTER,QUARTER_DOTTED,QUARTER_TRIPLET,
    EIGTH,EIGTH_DOTTED,EIGTH_TRIPLET,
    SIXTEENTH,SIXTEENTH_DOTTED,SIXTEENTH_TRIPLET,
    THIRTY2ND,THIRTY2ND_DOTTED,THIRTY2ND_TRIPLET
};

unsigned char BPM = 120;        //the tempo
unsigned char PPQN = 48;        //pulses per quarter note
unsigned char PRESCALER = 4;    //timer prescaler
unsigned char OCTAVES = 3;      //octave range of arpeggio (maximum of 4)
unsigned char NOTE_LENGTH_PULSES = SIXTEENTH;  //note length

//reset on key press, reset on key release
__bit RESET_ON_KEY_PRESS;
__bit RESET_ON_KEY_RELEASE;

//percent of note length (legato = 100%, staccato = 50%, very short = 25%)
//10%, 25%, 50%, 75%, 90%, 100%
//unsigned char GATE_TIME = 100;    //no code for this setting (leave commented out)

//arpeggio - latch the chord (continue playing after releasing keys if 1)
__bit LATCH;

//how to un-latch the notes
#define ALL 0
#define ONE_AT_A_TIME 1
__bit UN_LATCH_MODE;

//if ON, pressing a note will automatically add to the arpeggio
__bit AUTO_LATCH;
__bit latch_was_pressed;

//re-randomize arpeggio at end of arpeggio, or on BUTTON PRESS
__bit AUTO_RANDOMIZE;
#define AUTOMATICALLY 0
#define ONCE_PER_PRESS 1

//ARPEGGIO TYPE
unsigned char ARPEGGIO_TYPE = UP;
//STARTING DIRECTION OF ARPEGGIO
// *must* set startingDirection if ARPEGGIO_TYPE set to DOWN or DOWN_UP arpeggio at compile time!
unsigned char startingDirection;
//SKIP FIRST AND LAST NOTES OF ARPEGGIO
__bit skipFirstLast;

//wait to finish last playing note (one note length, or immediate)
void wait_one_pulse (unsigned char mode);
//immediate or wait
#define immediate 0
#define finishLast 1

//store last note mode
__bit lastNoteMode;
//last note mode on key press
__bit LAST_NOTE_MODE_KEY_PRESS;
//last note mode on key release
__bit LAST_NOTE_MODE_KEY_RELEASE;
//last note mode on transpose
__bit LAST_NOTE_MODE_TRANSPOSE;
//last note mode on reset
__bit LAST_NOTE_MODE_RESET;

//transmit last noteOff() before turning off arpeggiator
__bit finishLastNote;
__bit suppress_note_on;
__bit suppress_note_off;

//variables of 'playArpeggio()'
unsigned char which_note = 0; //changed to 'signed'
unsigned char last_note = 0; //changed to 'signed'
signed char which_octave = 0;
signed char last_octave = 0;
__bit overflow;
__bit octave_overflow;

signed char stored_octave = 0;  //temp store the octave
signed char parallel = 0;   //stores last key pressed (for note off on last key release)

__bit note_off_was_sent;    //suppress extra noteOff()s @ pitch C4

__bit flag1;                //suppress a note off at end of arpeggio
__bit flag2;                //suppress a note off at end of octaves

//this bit is un implemented for now (might be useful for a step sequencer update)
__bit DISPLAY_STEP_NUMBER;  //display NUM_NOTES_PRESSED, which_note +1

const unsigned char MAX_NUM_NOTES = 16; //maximum number of notes in the arpeggio
unsigned char NUM_NOTES_PRESSED = 0;    //number of notes that are playing
unsigned char ARRAY_INDEX = 0;          //keeps track of number of notes in the arpeggio array

//commented this out!
//unsigned char ARPEGGIO[MAX_NUM_NOTES] = {C,D,E,F,G,A,B,C2}; //array of notes in the arpeggio (as pressed)
//unsigned char ARPEGGIO_SORTED[MAX_NUM_NOTES] = {C,D,E,F,G,A,B,C2}; //sorted array
//unsigned char ARPEGGIO_RANDOM[MAX_NUM_NOTES] = {C,D,E,F,G,A,B,C2}; //random array

//commented this in!

//{0,0,0,0,0,0,0,0};
unsigned char ARPEGGIO[MAX_NUM_NOTES] = {0}; //array of notes in the arpeggio (as pressed)
unsigned char ARPEGGIO_SORTED[MAX_NUM_NOTES] = {0}; //sorted array
unsigned char ARPEGGIO_RANDOM[MAX_NUM_NOTES] = {0}; //random array

unsigned char *arpeggioPtr;     //pointer to which array to play in playArpeggio()

unsigned short TIMER_PRELOAD;   //starting value of TIMER0 (counts up to 0xFFFF to generate 1 pulse)
unsigned char TIMER_OVERFLOWS;  //counts number of timer overflows in ISR

#endif