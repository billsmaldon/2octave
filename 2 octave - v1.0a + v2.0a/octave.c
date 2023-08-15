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

#include "octave.h"
#include "arpeggio.h"

void printThisNumber (signed int n) {
    DISPLAY_MODE = DIGITS;
    DIGIT_MODE = BCD;
    number_to_display = n;
}

// *** TRANSPOSE USING SHIFT + KEYBOARD
void keyboardTranspose(void) {

    static signed char semitone_temp;
    static __bit keyPress;

    if(button_state_now == (BUTTON_27 | BUTTON_0))
    {
        semitone_temp = -12;
        keyPress = 1;
    }
    if(button_state_now == (BUTTON_27 | BUTTON_1))
    {
        semitone_temp = -11;
        keyPress = 1;
    }
    if(button_state_now == (BUTTON_27 | BUTTON_2))
    {
        semitone_temp = -10;
        keyPress = 1;
    }
    if(button_state_now == (BUTTON_27 | BUTTON_3))
    {
        semitone_temp = -9;
        keyPress = 1;
    }
    if(button_state_now == (BUTTON_27 | BUTTON_4))
    {
        semitone_temp = -8;
        keyPress = 1;
    }
    if(button_state_now == (BUTTON_27 | BUTTON_5))
    {
        semitone_temp = -7;
        keyPress = 1;
    }
    if(button_state_now == (BUTTON_27 | BUTTON_6))
    {
        semitone_temp = -6;
        keyPress = 1;
    }
    if(button_state_now == (BUTTON_27 | BUTTON_7))
    {
        semitone_temp = -5;
        keyPress = 1;
    }
    if(button_state_now == (BUTTON_27 | BUTTON_8))
    {
        semitone_temp = -4;
        keyPress = 1;
    }
    if(button_state_now == (BUTTON_27 | BUTTON_9))
    {
        semitone_temp = -3;
        keyPress = 1;
    }
    if(button_state_now == (BUTTON_27 | BUTTON_10))
    {
        semitone_temp = -2;
        keyPress = 1;
    }    
    if(button_state_now == (BUTTON_27 | BUTTON_11))
    {
        semitone_temp = -1;
        keyPress = 1;
    }    
    if(button_state_now == (BUTTON_27 | BUTTON_12))
    {
        semitone_temp = 0;
        keyPress = 1;
    }    
    if(button_state_now == (BUTTON_27 | BUTTON_13))
    {
        semitone_temp = 1;
        keyPress = 1;
    }
    if(button_state_now == (BUTTON_27 | BUTTON_14))
    {
        semitone_temp = 2;
        keyPress = 1;
    }
    if(button_state_now == (BUTTON_27 | BUTTON_15))
    {
        semitone_temp = 3;
        keyPress = 1;
    }
    if(button_state_now == (BUTTON_27 | BUTTON_16))
    {
        semitone_temp = 4;
        keyPress = 1;
    }
    if(button_state_now == (BUTTON_27 | BUTTON_17))
    {
        semitone_temp = 5;
        keyPress = 1;
    }
    if(button_state_now == (BUTTON_27 | BUTTON_18))
    {
        semitone_temp = 6;
        keyPress = 1;
    }
    if(button_state_now == (BUTTON_27 | BUTTON_19))
    {
        semitone_temp = 7;
        keyPress = 1;
    }
    if(button_state_now == (BUTTON_27 | BUTTON_20))
    {
        semitone_temp = 8;
        keyPress = 1;
    }
    if(button_state_now == (BUTTON_27 | BUTTON_21))
    {
        semitone_temp = 9;
        keyPress = 1;
    }
    if(button_state_now == (BUTTON_27 | BUTTON_22))
    {
        semitone_temp = 10;
        keyPress = 1;
    }
    if(button_state_now == (BUTTON_27 | BUTTON_23))
    {
        semitone_temp = 11;
        keyPress = 1;
    }
    if(button_state_now == (BUTTON_27 | BUTTON_24))
    {
        semitone_temp = 12;
        keyPress = 1;
    }    
    
    if(keyPress == 1) {
    
        //only when arpeggio is LATCHED and ONE OR MORE notes are pressed
        if((LATCH == 1) && (NUM_NOTES_PRESSED > 0)) {

            //wait for last note to finish
            wait_one_pulse(LAST_NOTE_MODE_TRANSPOSE);
                
            //call asynchronous noteOff
            //key_press_release_note_off();
            if(note_off_was_sent == 0) {key_press_release_note_off();}

            //need to set suppress_note_off and flag2 for perfect noteOff()
            suppress_note_off = 1;
            
            flag1 = 1; // added this! ---> NEED THIS flag bit = 1 for correct noteOff
            
            flag2 = 1;
        }
    
        //fixed this!
        if (semitone_temp > 12) {semitone_temp = 12;}
        if (semitone_temp < -12) {semitone_temp = -12;}
        semitone = semitone_temp;
        printThisNumber(semitone);
        keyPress = 0;
    }
}

void doTheLatch(void){
    LATCH = 1;
    latch_was_pressed = 1; //added this!
    DISPLAY_MODE = STRING;
    strcpy(string_to_display, "HoLd");    
}

void doTheUnLatch(void){
    
            LATCH = 0;
            ON_OFF = 0;

            //must call playThisNote(), playThisNote8(), playThisNotePentatonic() *for un-latch*
                
                if(NUM_NOTES_PRESSED > 0) {

                    static __bit once;  //need this bit to only call playThisNote() *once*

                    parallel = 25; //must set parallel out of keyboard range!
                    
                    //CHROMATIC SCALE, TRIADS, SEVENTH CHORDS
                    if ((KEYBOARD_MODE == CHROMATIC) || KEYBOARD_MODE == TRIAD || KEYBOARD_MODE == SEVENTH){

                        if((ARPEGGIO_TYPE == AS_PRESSED) || (ARPEGGIO_TYPE == RANDOM) || (ARPEGGIO_TYPE == RANDOM_NON_REPEATING) && (once == 0)){
                            playThisNote(ARPEGGIO[0]);
                            once = 1;
                        }
                        if((ARPEGGIO_TYPE == UP) || (ARPEGGIO_TYPE == UP_DOWN) && (once == 0)){                
                            playThisNote(ARPEGGIO_SORTED[0]);
                            once = 1;
                        }
                        if((ARPEGGIO_TYPE == DOWN) || (ARPEGGIO_TYPE == DOWN_UP) && (once == 0)){
                            playThisNote(ARPEGGIO_SORTED[NUM_NOTES_PRESSED - 1]);
                            once = 1;
                        }
                    }
                    //MAJOR SCALE, MINOR SCALE, MODES, DIATONIC TRIADS, DIATONIC 7TH CHORDS
                    if ((KEYBOARD_MODE == MAJOR) || (KEYBOARD_MODE == MINOR) || (KEYBOARD_MODE == MODES) || (KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) || (KEYBOARD_MODE == DIATONIC_TRIAD_MINOR)|| (KEYBOARD_MODE == DIATONIC_7TH_MAJOR) || (KEYBOARD_MODE == DIATONIC_7TH_MINOR) && (once == 0)) {
                        playThisNote8(0,0);
                        once = 1;
                    }
                    //PENTATONIC_MAJOR, PENTATONIC_MINOR
                    if ((KEYBOARD_MODE == PENTATONIC_MAJOR) || (KEYBOARD_MODE == PENTATONIC_MINOR) && (once == 0)){
                        playThisNotePentatonic(0,0);
                        once = 1;
                    }                    
                    
                    once = 0; //clear this bit here!
                }
                
            //delete note from arpeggio
            if((UN_LATCH_MODE == ONE_AT_A_TIME) && (latch_was_pressed == 1) && (NUM_NOTES_PRESSED > 1)){
                DISPLAY_MODE = STRING;
                strcpy(string_to_display, " dEL");
            }
            
            //last note remaining in arpeggio
            //if((UN_LATCH_MODE == ONE_AT_A_TIME) && (latch_was_pressed == 0) && (NUM_NOTES_PRESSED == 1)){
            if((UN_LATCH_MODE == ONE_AT_A_TIME) && (NUM_NOTES_PRESSED == 1)){
                DISPLAY_MODE = STRING;
                strcpy(string_to_display, "LaSt");
            }            
            
            //auto latch is ON
            //if((AUTO_LATCH == 1) && (latch_was_pressed == 1)){
            if((AUTO_LATCH == 1) && (latch_was_pressed == 1) && ((UN_LATCH_MODE == ALL) || (UN_LATCH_MODE == ONE_AT_A_TIME)) && (NUM_NOTES_PRESSED == 0)){
                NUM_NOTES_PRESSED = 0;
                ARRAY_INDEX = 0;              
                //LATCH = 1; //leave this commented out!
                DISPLAY_MODE = STRING;
                strcpy(string_to_display, "Auto");
            }

            //MIGHT NEED TO OR WITH 'ONE_AT_A_TIME'
            //if(((UN_LATCH_MODE == ALL) || (UN_LATCH_MODE == ONE_AT_A_TIME)) && (latch_was_pressed == 1) && (NUM_NOTES_PRESSED == 0)){
            
            //LATCH is OFF
            //added latch_was_pressed == 0
            if((LATCH == 0) && ((UN_LATCH_MODE == ALL) || (UN_LATCH_MODE == ONE_AT_A_TIME)) && (NUM_NOTES_PRESSED == 0)){
                NUM_NOTES_PRESSED = 0;
                ARRAY_INDEX = 0;
                DISPLAY_MODE = STRING;
                strcpy(string_to_display, " oFF");
            }    
}

//sets octave/semitone
void processOctave(void) {
    
    // THIS BLOCK OF CODE ---> SHIFT AND DRUM BUTTONS
    // only set/clear LATCH and other arpeggiator functions if the ARPEGGIATOR is ON
    // makes room for other use of SHIFT + DRUM buttons (if ARPEGGIATOR is OFF)
    if(ARPEGGIO_ON == 1) {
    
        // *** LATCH ON ***
        //if((button_state_now | drum_button_state_now ) == (BUTTON_27 | DRUM_BUTTON_0))
        if((button_state_now & BUTTON_27) && (drum_button_state_now & DRUM_BUTTON_0))        
        {
            /*
            LATCH = 1;
            latch_was_pressed = 1; //added this!
            DISPLAY_MODE = STRING;
            strcpy(string_to_display, "HoLd");
            */
            doTheLatch();
        }
    
        // *** LATCH OFF ***
        //if((button_state_now | drum_button_state_now ) == (BUTTON_27 | DRUM_BUTTON_1))
        if((button_state_now & BUTTON_27) && (drum_button_state_now & DRUM_BUTTON_1)) {
            
            doTheUnLatch();
            
            /*
            LATCH = 0;
            ON_OFF = 0;

            //must call playThisNote(), playThisNote8(), playThisNotePentatonic() *for un-latch*
                
                if(NUM_NOTES_PRESSED > 0) {

                    static __bit once;  //need this bit to only call playThisNote() *once*

                    parallel = 25; //must set parallel out of keyboard range!
                    
                    //CHROMATIC SCALE, TRIADS, SEVENTH CHORDS
                    if ((KEYBOARD_MODE == CHROMATIC) || KEYBOARD_MODE == TRIAD || KEYBOARD_MODE == SEVENTH){

                        if((ARPEGGIO_TYPE == AS_PRESSED) || (ARPEGGIO_TYPE == RANDOM) || (ARPEGGIO_TYPE == RANDOM_NON_REPEATING) && (once == 0)){
                            playThisNote(ARPEGGIO[0]);
                            once = 1;
                        }
                        if((ARPEGGIO_TYPE == UP) || (ARPEGGIO_TYPE == UP_DOWN) && (once == 0)){                
                            playThisNote(ARPEGGIO_SORTED[0]);
                            once = 1;
                        }
                        if((ARPEGGIO_TYPE == DOWN) || (ARPEGGIO_TYPE == DOWN_UP) && (once == 0)){
                            playThisNote(ARPEGGIO_SORTED[NUM_NOTES_PRESSED - 1]);
                            once = 1;
                        }
                    }
                    //MAJOR SCALE, MINOR SCALE, MODES, DIATONIC TRIADS, DIATONIC 7TH CHORDS
                    if ((KEYBOARD_MODE == MAJOR) || (KEYBOARD_MODE == MINOR) || (KEYBOARD_MODE == MODES) || (KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) || (KEYBOARD_MODE == DIATONIC_TRIAD_MINOR)|| (KEYBOARD_MODE == DIATONIC_7TH_MAJOR) || (KEYBOARD_MODE == DIATONIC_7TH_MINOR) && (once == 0)) {
                        playThisNote8(0,0);
                        once = 1;
                    }
                    //PENTATONIC_MAJOR, PENTATONIC_MINOR
                    if ((KEYBOARD_MODE == PENTATONIC_MAJOR) || (KEYBOARD_MODE == PENTATONIC_MINOR) && (once == 0)){
                        playThisNotePentatonic(0,0);
                        once = 1;
                    }                    
                    
                    once = 0; //clear this bit here!
                }
                
            //delete note from arpeggio
            if((UN_LATCH_MODE == ONE_AT_A_TIME) && (latch_was_pressed == 1) && (NUM_NOTES_PRESSED > 1)){
                DISPLAY_MODE = STRING;
                strcpy(string_to_display, " dEL");
            }
            
            //last note remaining in arpeggio
            //if((UN_LATCH_MODE == ONE_AT_A_TIME) && (latch_was_pressed == 0) && (NUM_NOTES_PRESSED == 1)){
            if((UN_LATCH_MODE == ONE_AT_A_TIME) && (NUM_NOTES_PRESSED == 1)){
                DISPLAY_MODE = STRING;
                strcpy(string_to_display, "LaSt");
            }            
            
            //auto latch is ON
            //if((AUTO_LATCH == 1) && (latch_was_pressed == 1)){
            if((AUTO_LATCH == 1) && (latch_was_pressed == 1) && ((UN_LATCH_MODE == ALL) || (UN_LATCH_MODE == ONE_AT_A_TIME)) && (NUM_NOTES_PRESSED == 0)){
                NUM_NOTES_PRESSED = 0;
                ARRAY_INDEX = 0;              
                //LATCH = 1; //leave this commented out!
                DISPLAY_MODE = STRING;
                strcpy(string_to_display, "Auto");
            }

            //MIGHT NEED TO OR WITH 'ONE_AT_A_TIME'
            //if(((UN_LATCH_MODE == ALL) || (UN_LATCH_MODE == ONE_AT_A_TIME)) && (latch_was_pressed == 1) && (NUM_NOTES_PRESSED == 0)){
            
            //LATCH is OFF
            //added latch_was_pressed == 0
            if((LATCH == 0) && ((UN_LATCH_MODE == ALL) || (UN_LATCH_MODE == ONE_AT_A_TIME)) && (NUM_NOTES_PRESSED == 0)){
                NUM_NOTES_PRESSED = 0;
                ARRAY_INDEX = 0;
                DISPLAY_MODE = STRING;
                strcpy(string_to_display, " oFF");
            }
            */
        }
    
        // *** RE-RANDOMIZE the ARPEGGIO ***
        //if((button_state_now | drum_button_state_now ) == (BUTTON_27 | DRUM_BUTTON_2)){
        if((button_state_now & BUTTON_27) && (drum_button_state_now & DRUM_BUTTON_2)){
        
            //manually randomize here!
            if(ARPEGGIO_TYPE == RANDOM) {random_pitches();}
            if(ARPEGGIO_TYPE == RANDOM_NON_REPEATING){random_pitches_non_repeating();}
            
            DISPLAY_MODE = STRING;
            strcpy(string_to_display, "rAnd");             
        
        }
    
        // *** RESET the ARPEGGIO ***
        //if((button_state_now | drum_button_state_now ) == (BUTTON_27 | DRUM_BUTTON_3)){
        if((button_state_now & BUTTON_27) && (drum_button_state_now & DRUM_BUTTON_3)){    
        
            //wait for last note to finish
            wait_one_pulse(LAST_NOTE_MODE_RESET);
            note_off_was_sent = 1;
            key_press_release_note_off();
        
            //reset arpeggio
            resetArpeggio();

            //next noteOn
            TIMER_OVERFLOWS = 0;
            
            DISPLAY_MODE = STRING;
            strcpy(string_to_display, "rSEt");
        }
    }
    
    //octave++
    if(button_state_now == BUTTON_26){
        if ((octave * 12 + semitone) <= 60) { // !!! DONE !!!

            //only when arpeggio is LATCHED and ONE OR MORE notes are pressed
            if((LATCH == 1) && (NUM_NOTES_PRESSED > 0)) {

                //wait for last note to finish
                wait_one_pulse(LAST_NOTE_MODE_TRANSPOSE);
                
                //call asynchronous noteOff
                //key_press_release_note_off();
                if(note_off_was_sent == 0) {key_press_release_note_off();}

                //need to set suppress_note_off and flag2 for perfect noteOff()
                suppress_note_off = 1;
                
                flag1 = 1; // added this! ---> NEED THIS flag bit = 1 for correct noteOff                
                flag2 = 1;
            }            
            
            octave++;
            if (octave > 7) {octave = 7;}            
            
            printThisNumber(octave);
        }
    }
    
    //octave--
    if(button_state_now == BUTTON_25){
        if ((octave * 12 + semitone) >= 12) { // !!! DONE !!!
            
            //only when arpeggio is LATCHED and ONE OR MORE notes are pressed
            if((LATCH == 1) && (NUM_NOTES_PRESSED > 0)) {

                //wait for last note to finish
                wait_one_pulse(LAST_NOTE_MODE_TRANSPOSE);
                
                //call asynchronous noteOff
                //key_press_release_note_off();
                if(note_off_was_sent == 0) {key_press_release_note_off();}

                //need to set suppress_note_off and flag2 for perfect noteOff()
                suppress_note_off = 1;
                
                flag1 = 1; // added this! ---> NEED THIS flag bit = 1 for correct noteOff                
                
                flag2 = 1;
            }
            
            octave--;
            if (octave < 0) {octave = 0;}
            
            printThisNumber(octave);

        }
    }
    
    //semitone transpose (uses modifier)
    //BUTTON_27 is modifier
    
    //semitone++
    if(button_state_now == (BUTTON_26 | BUTTON_27)){
        
        if ((octave * 12 + semitone) < 72) {  // !!! ++ semitone needs work !!!
            
            //only when arpeggio is LATCHED and ONE OR MORE notes are pressed
            if((LATCH == 1) && (NUM_NOTES_PRESSED > 0)) {

                //wait for last note to finish
                wait_one_pulse(LAST_NOTE_MODE_TRANSPOSE);
                
                //call asynchronous noteOff
                //key_press_release_note_off();
                if(note_off_was_sent == 0) {key_press_release_note_off();}

                //need to set suppress_note_off and flag2 for perfect noteOff()
                suppress_note_off = 1;
                
                flag1 = 1; // added this! ---> NEED THIS flag bit = 1 for correct noteOff                
                flag2 = 1;
            }
 
            if (TRANSPOSE_MODE == HALF_STEP) {
                semitone++;
                if (semitone > 12) {semitone = 12;}
            }
            
            if (TRANSPOSE_MODE == CIRCLE_OF_FIFTHS) {
                semitone = (semitone +=7) % 12;
            }
            
            printThisNumber(semitone);
        }
    }
    
    //semitone--
    if(button_state_now == (BUTTON_25 | BUTTON_27)){
        
        if ((octave * 12 + semitone) > 0 ) {
        //if ((octave * 12 + semitone) >= 12 ) {
            
            //only when arpeggio is LATCHED and ONE OR MORE notes are pressed
            if((LATCH == 1) && (NUM_NOTES_PRESSED > 0)) {    

                //wait for last note to finish
                wait_one_pulse(LAST_NOTE_MODE_TRANSPOSE);
        
                //call asynchronous noteOff
                //key_press_release_note_off();
                if(note_off_was_sent == 0) {key_press_release_note_off();}
                
                //need to set suppress_note_off and flag2 for perfect noteOff()
                suppress_note_off = 1;
                
                flag1 = 1; // added this! ---> NEED THIS flag bit = 1 for correct noteOff                
                flag2 = 1;
            }
            
            if (TRANSPOSE_MODE == HALF_STEP) {
                semitone--;
                if (semitone < -12) {semitone = -12;}
            }
            
            if (TRANSPOSE_MODE == CIRCLE_OF_FIFTHS) {
                semitone = (semitone -=7) % 12;
            }
            
            printThisNumber(semitone);
        }
    }
}