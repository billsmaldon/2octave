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

#include "keyboard.h"
#include "arpeggio.h"
#include "octave.h"

//select keyboard mode
void processKeyboard(void) {
    
    /*
    //end mismatch on boot-up
    static __bit buttonStart;
    if(buttonStart == 0){
        button_state_last = button_state_now;
        buttonStart = 1;
    }    
    */
    
    //CHROMATIC SCALE, TRIADS, SEVENTH CHORDS    
    if ((KEYBOARD_MODE == CHROMATIC) || KEYBOARD_MODE == TRIAD || KEYBOARD_MODE == SEVENTH) {keyboard_all_note_efficient();} //play the keyboard
    //MAJOR SCALE, MINOR SCALE, MODES, DIATONIC TRIADS, DIATONIC 7TH CHORDS
    if ((KEYBOARD_MODE == MAJOR) || (KEYBOARD_MODE == MINOR) || (KEYBOARD_MODE == MODES) || (KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) || (KEYBOARD_MODE == DIATONIC_TRIAD_MINOR)|| (KEYBOARD_MODE == DIATONIC_7TH_MAJOR) || (KEYBOARD_MODE == DIATONIC_7TH_MINOR)) {keyboard_eight_note_efficient();}
    //add function for pentatonic scales
    if ((KEYBOARD_MODE == PENTATONIC_MAJOR) || (KEYBOARD_MODE == PENTATONIC_MINOR)) {keyboard_sharps_only_efficient();}
}

void playThisNotePentatonic(unsigned char pitch, unsigned char index) {

    if(ARPEGGIO_ON == 0){

        if(KEYBOARD_MODE == PENTATONIC_MAJOR) {
            if(ON_OFF == 1) {noteOn(channel,pentatonic_major_key[index],velocity);}
            if(ON_OFF == 0) {noteOff(channel,pentatonic_major_key[index],velocity);}
        }
    
        if(KEYBOARD_MODE == PENTATONIC_MINOR) {
            if(ON_OFF == 1) {noteOn(channel,pentatonic_minor_key[index],velocity);}
            if(ON_OFF == 0) {noteOff(channel,pentatonic_minor_key[index],velocity);}
        }    
    }    
    
    //play arpeggio of pentatonic major/pentatonic minor
    if(ARPEGGIO_ON == 1){
        
        unsigned char temp_pitch;
        
        if(KEYBOARD_MODE == PENTATONIC_MAJOR) {
            temp_pitch = pentatonic_major_key[index];
        }
    
        if(KEYBOARD_MODE == PENTATONIC_MINOR) {
           temp_pitch = pentatonic_minor_key[index];
        }

        if(ON_OFF == 1) {
            
            //turn off the timer
            TMR0ON = 0;
            
            parallel = temp_pitch; //'temp_pitch' or 'pitch'

            //wait one pulse
            if(NUM_NOTES_PRESSED > 0){            
                wait_one_pulse(LAST_NOTE_MODE_KEY_PRESS);
                if(note_off_was_sent == 0) {key_press_release_note_off();}
                TIMER_OVERFLOWS = 0;
            }

            add_notes_to_arpeggio(temp_pitch);
            //add_notes_to_arpeggio(pentatonic_major_key[index]);
            
            
            //if(KEYBOARD_MODE == PENTATONIC_MAJOR) {
            //    add_notes_to_arpeggio(pentatonic_major_key[index]);
            //}
            //if(KEYBOARD_MODE == PENTATONIC_MINOR) {
            //    add_notes_to_arpeggio(pentatonic_minor_key[index]);
            //}            

            //for auto-latch
            if(LATCH == 0) {latch_was_pressed = 0;}            

           //finish setting up arpeggio
            finish_arpeggio_setup();            
            
            //turn timer ON
            TMR0ON = 1;
        }
            
        if((ON_OFF == 0) && (LATCH == 0)) {

            //turn off the timer
            TMR0ON = 0;

            //wait one pulse
            if(NUM_NOTES_PRESSED > 0){
                wait_one_pulse(LAST_NOTE_MODE_KEY_RELEASE);
                if(note_off_was_sent == 0) {key_press_release_note_off();}
                TIMER_OVERFLOWS = 0;
            }

            delete_notes_from_arpeggio(temp_pitch);
            //delete_notes_from_arpeggio(pentatonic_major_key[index]);

            //if(KEYBOARD_MODE == PENTATONIC_MAJOR) {
            //    delete_notes_from_arpeggio(pentatonic_major_key[index]);
            //}
            //if(KEYBOARD_MODE == PENTATONIC_MINOR) {
            //    delete_notes_from_arpeggio(pentatonic_minor_key[index]);
            //}             

            if(temp_pitch == parallel){NUM_NOTES_PRESSED = 0;} // changed from 'pitch' to 'temp_pitch'

            // press UN_LATCH twice and LATCH is set to '0'
            if((AUTO_LATCH == 1) && (latch_was_pressed == 1)){
                LATCH = 1;
            }

            //un-latch ALL notes
            if((UN_LATCH_MODE == ALL) && (latch_was_pressed == 1)){
                NUM_NOTES_PRESSED = 0;
                ARRAY_INDEX = 0;
            }
 
            //finish setting up arpeggio
            finish_arpeggio_setup();
            
            //turn timer ON
            TMR0ON = 1;
        }
    }
}

void keyboard_sharps_only_efficient(void){
    
    unsigned char pitch;    //is a pitch
    unsigned char index;    //is an array index (different from pitch)
    
    // *** NOTE ON ***
    if((button_state_now & BUTTON_1) && !(button_state_now & BUTTON_27) && !keyboard.SW2){ //!keyboard.SW1
        pitch = Cs;
        index = 0;
        ON_OFF = 1;
        playThisNotePentatonic(pitch, index);
        keyboard.SW2 = 1;
    }
    if((button_state_now & BUTTON_3) && !(button_state_now & BUTTON_27) && !keyboard.SW4){ //!keyboard.SW1
        pitch = Ds;
        index = 1;
        ON_OFF = 1;
        playThisNotePentatonic(pitch, index);
        keyboard.SW4 = 1;
    }
    if((button_state_now & BUTTON_6) && !(button_state_now & BUTTON_27) && !keyboard.SW7){ //!keyboard.SW1
        pitch = Fs;
        index = 2;
        ON_OFF = 1;
        playThisNotePentatonic(pitch, index);
        keyboard.SW7 = 1;
    }
    if((button_state_now & BUTTON_8) && !(button_state_now & BUTTON_27) && !keyboard.SW9){ //!keyboard.SW1
        pitch = Gs;
        index = 3;
        ON_OFF = 1;
        playThisNotePentatonic(pitch, index);
        keyboard.SW9 = 1;
    }
    if((button_state_now & BUTTON_10) && !(button_state_now & BUTTON_27) && !keyboard.SW11){ //!keyboard.SW1
        pitch = As;
        index = 4;
        ON_OFF = 1;
        playThisNotePentatonic(pitch, index);
        keyboard.SW11 = 1;
    }
    //octave 2
    if((button_state_now & BUTTON_13) && !(button_state_now & BUTTON_27) && !keyboard.SW14){ //!keyboard.SW1
        pitch = C2s;
        index = 5;
        ON_OFF = 1;
        playThisNotePentatonic(pitch, index);
        keyboard.SW14 = 1;
    }
    if((button_state_now & BUTTON_15) && !(button_state_now & BUTTON_27) && !keyboard.SW16){ //!keyboard.SW1
        pitch = D2s;
        index = 6;
        ON_OFF = 1;
        playThisNotePentatonic(pitch, index);
        keyboard.SW16 = 1;
    }
    if((button_state_now & BUTTON_18) && !(button_state_now & BUTTON_27) && !keyboard.SW19){ //!keyboard.SW1
        pitch = F2s;
        index = 7;
        ON_OFF = 1;
        playThisNotePentatonic(pitch, index);
        keyboard.SW19 = 1;
    }
    if((button_state_now & BUTTON_20) && !(button_state_now & BUTTON_27) && !keyboard.SW21){ //!keyboard.SW1
        pitch = G2s;
        index = 8;
        ON_OFF = 1;
        playThisNotePentatonic(pitch, index);
        keyboard.SW21 = 1;
    }
    if((button_state_now & BUTTON_22) && !(button_state_now & BUTTON_27) && !keyboard.SW23){ //!keyboard.SW1
        pitch = A2s;
        index = 9;
        ON_OFF = 1;
        playThisNotePentatonic(pitch, index);
        keyboard.SW23 = 1;
    }    
    
    // *** NOTE OFF ***
    if(((button_state_last & BUTTON_1)) && ((button_state_now & BUTTON_1) == 0) && keyboard.SW2) {
        pitch = Cs;
        index = 0;
        ON_OFF = 0;
        playThisNotePentatonic(pitch, index);
        keyboard.SW2 = 0;
    }
    if(((button_state_last & BUTTON_3)) && ((button_state_now & BUTTON_3) == 0) && keyboard.SW4) {
        pitch = Ds;
        index = 1;
        ON_OFF = 0;
        playThisNotePentatonic(pitch, index);
        keyboard.SW4 = 0;
    }
    if(((button_state_last & BUTTON_6)) && ((button_state_now & BUTTON_6) == 0) && keyboard.SW7) {
        pitch = Fs;
        index = 2;
        ON_OFF = 0;
        playThisNotePentatonic(pitch, index);
        keyboard.SW7 = 0;
    }
    if(((button_state_last & BUTTON_8)) && ((button_state_now & BUTTON_8) == 0) && keyboard.SW9) {
        pitch = Gs;
        index = 3;
        ON_OFF = 0;
        playThisNotePentatonic(pitch, index);
        keyboard.SW9 = 0;
    }
    if(((button_state_last & BUTTON_10)) && ((button_state_now & BUTTON_10) == 0) && keyboard.SW11) {
        pitch = As;
        index = 4;
        ON_OFF = 0;
        playThisNotePentatonic(pitch, index);
        keyboard.SW11 = 0;
    }
    
    //next octave
    if(((button_state_last & BUTTON_13)) && ((button_state_now & BUTTON_13) == 0) && keyboard.SW14) {
        pitch = C2s;
        index = 5;
        ON_OFF = 0;
        playThisNotePentatonic(pitch, index);
        keyboard.SW14 = 0;
    }
    if(((button_state_last & BUTTON_15)) && ((button_state_now & BUTTON_15) == 0) && keyboard.SW16) {
        pitch = D2s;
        index = 6;
        ON_OFF = 0;
        playThisNotePentatonic(pitch, index);
        keyboard.SW16 = 0;
    }
    if(((button_state_last & BUTTON_18)) && ((button_state_now & BUTTON_18) == 0) && keyboard.SW19) {
        pitch = F2s;
        index = 7;
        ON_OFF = 0;
        playThisNotePentatonic(pitch, index);
        keyboard.SW19 = 0;
    }
    if(((button_state_last & BUTTON_20)) && ((button_state_now & BUTTON_20) == 0) && keyboard.SW21) {
        pitch = G2s;
        index = 8;
        ON_OFF = 0;
        playThisNotePentatonic(pitch, index);
        keyboard.SW21 = 0;
    }
    if(((button_state_last & BUTTON_22)) && ((button_state_now & BUTTON_22) == 0) && keyboard.SW23) {
        pitch = A2s;
        index = 9;
        ON_OFF = 0;
        playThisNotePentatonic(pitch, index);
        keyboard.SW23 = 0;
    }    
}

void playTriad(unsigned char pitch){
    
    unsigned char *triad_p;     //points to a triad
    
       
    //selects a triad type
    switch (which_triad) {
        case major:
            triad_p = major_triad;
            break;
        case minor:
            triad_p = minor_triad;
            break;
        case augmented:
            triad_p = augmented_triad;
            break;
        case diminished:
            triad_p = diminished_triad;
            break;
        default:
            break;
    }
    
    // !!! LEFT OFF HERE !!!
    
    // press a key in a KEYBOARD_MODE
    // turn ENCODER to a different KEYBOARD_MODE
    // release the key and the wrong noteOff()s are sent!
    
    // KEYBOARD_MODE "last"
    // KEYBOARD_MODE "now"
    
    //play triad
    if(ARPEGGIO_ON == 0){
        for(unsigned char i = 0; i<3; i++){
            if(ON_OFF == 1) {noteOn(channel,triad_p[i] + pitch,velocity);}
            if(ON_OFF == 0) {noteOff(channel,triad_p[i] + pitch,velocity);}         
        }      
    }
    
    //play arpeggio
    if(ARPEGGIO_ON == 1){
        if(ON_OFF == 1) {
        
            TMR0ON = 0; //added this!

            //for asynchronous note off          
            parallel = pitch;
            
            //lets you latch a new chord to arpeggiate
            if(NUM_NOTES_PRESSED > 0){
                wait_one_pulse(LAST_NOTE_MODE_KEY_PRESS);
                if(note_off_was_sent == 0) {key_press_release_note_off();}
                TIMER_OVERFLOWS = 0;
            }

            for(unsigned char i = 0; i<3; i++){
                ARPEGGIO[i] = triad_p[i] + pitch;
            }
        
            NUM_NOTES_PRESSED = 3;
            //setupArpeggio();    //set arpeggioType
            
            //for auto-latch
            if(LATCH == 0) {latch_was_pressed = 0;}
            
            finish_arpeggio_setup();
            TMR0ON = 1;             //start TIMER0
            
            return;
        }

        if((ON_OFF == 0) && (LATCH == 0)) {

            if(NUM_NOTES_PRESSED > 0){
                wait_one_pulse(LAST_NOTE_MODE_KEY_RELEASE);
                if(note_off_was_sent == 0) {key_press_release_note_off();}
                TIMER_OVERFLOWS = 0; //for immediate noteOn() next
            }            

            //if pitch = last key pressed, turn off arpeggiator
            if(pitch == parallel){NUM_NOTES_PRESSED = 0;}

            // 'auto latch' if single key releases and one or more notes are still playing
            // set LATCH = 1 automatically, to keep adding notes to arpeggio (after deleting a note)
            // press UN_LATCH twice and LATCH is set to '0'
            if((AUTO_LATCH == 1) && (latch_was_pressed == 1)){
                LATCH = 1;
            }
            
            //changed this to !!!LOGICAL!!!
            //for un-latch
            if(((UN_LATCH_MODE == ALL) || (UN_LATCH_MODE == ONE_AT_A_TIME)) && (latch_was_pressed == 1)){
                NUM_NOTES_PRESSED = 0;
                ARRAY_INDEX = 0;
            }            

            finish_arpeggio_setup();
            TMR0ON = 1;
            return;
        }
    }        
}

void playSeventh(unsigned char pitch){
    
    unsigned char *seventh_p;   //points to a seventh chord
    
    //selects a seventh chord type
    switch (which_seventh) {
       case dominant7:
            seventh_p = dominant_7th;
            break;
        case major7:
            seventh_p = major_7th;
            break;
        case minor7:
            seventh_p = minor_7th;
            break;
        case half_diminished7:
            seventh_p = half_diminished_7th;
            break;
        case diminished7:
            seventh_p = diminished_7th;
            break;
        default:
            break;
    }        
    
    //play seventh chord
    if(ARPEGGIO_ON == 0){
        for(unsigned char i = 0; i<4; i++){
            if(ON_OFF == 1) {noteOn(channel,seventh_p[i] + pitch,velocity);}
            if(ON_OFF == 0) {noteOff(channel,seventh_p[i] + pitch,velocity);}         
        }
    }

    //play arpeggio
    if(ARPEGGIO_ON == 1){
        
        if(ON_OFF == 1) {
            
            TMR0ON = 0; //added this!
            
            //for asynchronous note off
            parallel = pitch;
            
            //lets you latch a new chord to arpeggiate
            if(NUM_NOTES_PRESSED > 0){
                wait_one_pulse(LAST_NOTE_MODE_KEY_PRESS);
                if(note_off_was_sent == 0) {key_press_release_note_off();}
                TIMER_OVERFLOWS = 0;
            }        

            for(unsigned char i = 0; i<4; i++){
                ARPEGGIO[i] = seventh_p[i] + pitch;
            }
        
            NUM_NOTES_PRESSED = 4;
            
            //for auto-latch
            if(LATCH == 0) {latch_was_pressed = 0;}
            
            finish_arpeggio_setup();
            TMR0ON = 1;             //start TIMER0
            
            return;
        }
    
        if((ON_OFF == 0) && (LATCH == 0)) {

            if(NUM_NOTES_PRESSED > 0){
                wait_one_pulse(LAST_NOTE_MODE_KEY_RELEASE);
                if(note_off_was_sent == 0) {key_press_release_note_off();}
                TIMER_OVERFLOWS = 0;
            }

            //if pitch = last key pressed, turn off arpeggiator
            if(pitch == parallel){NUM_NOTES_PRESSED = 0;}
            
            // 'auto latch' if single key releases and one or more notes are still playing
            // set LATCH = 1 automatically, to keep adding notes to arpeggio (after deleting a note)
            // press UN_LATCH twice and LATCH is set to '0'
            if((AUTO_LATCH == 1) && (latch_was_pressed == 1)){
                LATCH = 1;
            }
            
            //changed this to !!!LOGICAL!!!
            //for un-latch
            if(((UN_LATCH_MODE == ALL) || (UN_LATCH_MODE == ONE_AT_A_TIME)) && (latch_was_pressed == 1)){
                NUM_NOTES_PRESSED = 0;
                ARRAY_INDEX = 0;
            }          

            finish_arpeggio_setup();
            TMR0ON = 1;
            
            return;
        }
    }
}

void playThisNote(unsigned char pitch){
    
    if(KEYBOARD_MODE == CHROMATIC) {

        // FOR SINGLE PITCH KEYPRESS!!! (not arpeggio)
        if(ARPEGGIO_ON == 0){
            if(ON_OFF == 1) {noteOn(channel,pitch,velocity);}
            if(ON_OFF == 0) {noteOff(channel,pitch,velocity);}
        }
        
        //ARPEGGIO block of code!
        if(ARPEGGIO_ON == 1){
            
            if(ON_OFF == 1){
            
            //turn off the timer
            TMR0ON = 0;                
                
            parallel = pitch;

            //asynchronous note off
            if(NUM_NOTES_PRESSED > 0){    //commented out --- test!
                wait_one_pulse(LAST_NOTE_MODE_KEY_PRESS);
                if(note_off_was_sent == 0) {key_press_release_note_off();}
                TIMER_OVERFLOWS = 0;
            }

            //add notes to the arpeggio here
            add_notes_to_arpeggio(pitch);
            
            //for auto-latch
            if(LATCH == 0) {
                latch_was_pressed = 0;
            }
            
            //finish setting up arpeggio
            finish_arpeggio_setup();

            //turn timer ON
            TMR0ON = 1;
            
            return;
        }
 
        //LATCH off
        if((ON_OFF == 0) && (LATCH == 0)){
            
            //turn off the timer
            TMR0ON = 0;

            //asynchronous note off
            if(NUM_NOTES_PRESSED > 0){
                wait_one_pulse(LAST_NOTE_MODE_KEY_RELEASE);
                if(note_off_was_sent == 0) {key_press_release_note_off();}
                TIMER_OVERFLOWS = 0;
            }            

            //delete notes from arpeggio
            delete_notes_from_arpeggio(pitch);
            
            //if pitch = last key pressed, turn off arpeggiator
            if(pitch == parallel){NUM_NOTES_PRESSED = 0;} //comment this out!
            
            // 'auto latch' if single key releases and one or more notes are still playing
            // set LATCH = 1 automatically, to keep adding notes to arpeggio (after deleting a note)
            // press UN_LATCH twice and LATCH is set to '0'
            if((AUTO_LATCH == 1) && (latch_was_pressed == 1)){
                LATCH = 1;
            }
            
            //un-latch ALL notes
            if((UN_LATCH_MODE == ALL) && (latch_was_pressed == 1)){
                NUM_NOTES_PRESSED = 0;
                ARRAY_INDEX = 0;
            }

            //finish arpeggio setup
            finish_arpeggio_setup();
             
            //turn timer ON
            TMR0ON = 1;
            
            return;
            }
        }
    }
        
    if(KEYBOARD_MODE == TRIAD) {
        playTriad(pitch);
    }
        
    if(KEYBOARD_MODE == SEVENTH) {
        playSeventh(pitch);
    }    
}

//entire keyboard - efficient!
void keyboard_all_note_efficient(void){

    unsigned char pitch;

    // *** NOTE ON *** POLYPHONIC
    if((button_state_now & BUTTON_0) && !(button_state_now & BUTTON_27) && !keyboard.SW1) { //changed to '=='
        pitch = C;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW1 = 1;
    }
    
    if((button_state_now & BUTTON_1) && !(button_state_now & BUTTON_27) && !keyboard.SW2) {
        pitch = Cs;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW2 = 1;
    }
    
    if((button_state_now & BUTTON_2) && !(button_state_now & BUTTON_27) && !keyboard.SW3) {
        pitch = D;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW3 = 1;
    }
    if((button_state_now & BUTTON_3) && !(button_state_now & BUTTON_27) && !keyboard.SW4) {
        pitch = Ds;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW4 = 1;
    }
    if((button_state_now & BUTTON_4) && !(button_state_now & BUTTON_27) && !keyboard.SW5) {
        pitch = E;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW5 = 1;
    }
    if((button_state_now & BUTTON_5) && !(button_state_now & BUTTON_27) && !keyboard.SW6) {
        pitch = F;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW6 = 1;
    }
    if((button_state_now & BUTTON_6) && !(button_state_now & BUTTON_27) && !keyboard.SW7) {
        pitch = Fs;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW7 = 1;
    }
    if((button_state_now & BUTTON_7) && !(button_state_now & BUTTON_27) && !keyboard.SW8) {
        pitch = G;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW8 = 1;
    }
    if((button_state_now & BUTTON_8) && !(button_state_now & BUTTON_27) && !keyboard.SW9) {
        pitch = Gs;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW9 = 1;
    }
    if((button_state_now & BUTTON_9) && !(button_state_now & BUTTON_27) && !keyboard.SW10) {
        pitch = A;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW10 = 1;
    }
    if((button_state_now & BUTTON_10) && !(button_state_now & BUTTON_27) && !keyboard.SW11) {
        pitch = As;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW11 = 1;
    }
    if((button_state_now & BUTTON_11) && !(button_state_now & BUTTON_27) && !keyboard.SW12) {
        pitch = B;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW12 = 1;
    }
    if((button_state_now & BUTTON_12) && !(button_state_now & BUTTON_27) && !keyboard.SW13) {
        pitch = C2;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW13 = 1;
    }
    if((button_state_now & BUTTON_13) && !(button_state_now & BUTTON_27) && !keyboard.SW14) {
        pitch = C2s;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW14 = 1;
    }
    if((button_state_now & BUTTON_14) && !(button_state_now & BUTTON_27) && !keyboard.SW15) {
        pitch = D2;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW15 = 1;
    }
    if((button_state_now & BUTTON_15) && !(button_state_now & BUTTON_27) && !keyboard.SW16) {
        pitch = D2s;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW16 = 1;
    }
    if((button_state_now & BUTTON_16) && !(button_state_now & BUTTON_27) && !keyboard.SW17) {
        pitch = E2;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW17 = 1;
    }
    if((button_state_now & BUTTON_17) && !(button_state_now & BUTTON_27) && !keyboard.SW18) {
        pitch = F2;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW18 = 1;
    }
    if((button_state_now & BUTTON_18) && !(button_state_now & BUTTON_27) && !keyboard.SW19) {
        pitch = F2s;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW19 = 1;
    }
    if((button_state_now & BUTTON_19) && !(button_state_now & BUTTON_27) && !keyboard.SW20) {
        pitch = G2;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW20 = 1;
    }
    if((button_state_now & BUTTON_20) && !(button_state_now & BUTTON_27) && !keyboard.SW21) {
        pitch = G2s;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW21 = 1;
    }
    if((button_state_now & BUTTON_21) && !(button_state_now & BUTTON_27) && !keyboard.SW22) {
        pitch = A2;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW22 = 1;
    }
    if((button_state_now & BUTTON_22) && !(button_state_now & BUTTON_27) && !keyboard.SW23) {
        pitch = A2s;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW23 = 1;
    }
    if((button_state_now & BUTTON_23) && !(button_state_now & BUTTON_27) && !keyboard.SW24) {
        pitch = B2;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW24 = 1;
    }
    if((button_state_now & BUTTON_24) && !(button_state_now & BUTTON_27) && !keyboard.SW25) {
        pitch = C3;
        ON_OFF = 1;
        playThisNote(pitch);
        keyboard.SW25 = 1;
    }
    
    // *** NOTE OFF *** POLYPHONIC
    if(((button_state_last & BUTTON_0)) && ((button_state_now & BUTTON_0) == 0) && keyboard.SW1) {
        pitch = C;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW1 = 0;
    }
    if(((button_state_last & BUTTON_1)) && ((button_state_now & BUTTON_1) == 0) && keyboard.SW2) {
        pitch = Cs;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW2 = 0;
    }
    if(((button_state_last & BUTTON_2)) && ((button_state_now & BUTTON_2) == 0) && keyboard.SW3) {
        pitch = D;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW3 = 0;
    }
    if(((button_state_last & BUTTON_3)) && ((button_state_now & BUTTON_3) == 0) && keyboard.SW4) {
        pitch = Ds;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW4 = 0;
    }
    if(((button_state_last & BUTTON_4)) && ((button_state_now & BUTTON_4) == 0) && keyboard.SW5) {
        pitch = E;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW5 = 0;
    }
    if(((button_state_last & BUTTON_5)) && ((button_state_now & BUTTON_5) == 0) && keyboard.SW6) {
        pitch = F;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW6 = 0;
    }
    if(((button_state_last & BUTTON_6)) && ((button_state_now & BUTTON_6) == 0) && keyboard.SW7) {
        pitch = Fs;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW7 = 0;
    }
    if(((button_state_last & BUTTON_7)) && ((button_state_now & BUTTON_7) == 0) && keyboard.SW8) {
        pitch = G;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW8 = 0;
    }
    if(((button_state_last & BUTTON_8)) && ((button_state_now & BUTTON_8) == 0) && keyboard.SW9) {
        pitch = Gs;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW9 = 0;
    }
    if(((button_state_last & BUTTON_9)) && ((button_state_now & BUTTON_9) == 0) && keyboard.SW10) {
        pitch = A;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW10 = 0;
    }
    if(((button_state_last & BUTTON_10)) && ((button_state_now & BUTTON_10) == 0) && keyboard.SW11) {
        pitch = As;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW11 = 0;
    }
    if(((button_state_last & BUTTON_11)) && ((button_state_now & BUTTON_11) == 0) && keyboard.SW12) {
        pitch = B;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW12 = 0;
    }
    if(((button_state_last & BUTTON_12)) && ((button_state_now & BUTTON_12) == 0) && keyboard.SW13) {
        pitch = C2;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW13 = 0;
    }
    if(((button_state_last & BUTTON_13)) && ((button_state_now & BUTTON_13) == 0) && keyboard.SW14) {
        pitch = C2s;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW14 = 0;
    }
    if(((button_state_last & BUTTON_14)) && ((button_state_now & BUTTON_14) == 0) && keyboard.SW15) {
        pitch = D2;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW15 = 0;
    }
    if(((button_state_last & BUTTON_15)) && ((button_state_now & BUTTON_15) == 0) && keyboard.SW16) {
        pitch = D2s;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW16 = 0;
    }
    if(((button_state_last & BUTTON_16)) && ((button_state_now & BUTTON_16) == 0) && keyboard.SW17) {
        pitch = E2;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW17 = 0;
    }
    if(((button_state_last & BUTTON_17)) && ((button_state_now & BUTTON_17) == 0) && keyboard.SW18) {
        pitch = F2;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW18 = 0;
    }
    if(((button_state_last & BUTTON_18)) && ((button_state_now & BUTTON_18) == 0) && keyboard.SW19) {
        pitch = F2s;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW19 = 0;
    }
    if(((button_state_last & BUTTON_19)) && ((button_state_now & BUTTON_19) == 0) && keyboard.SW20) {
        pitch = G2;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW20 = 0;
    }
    if(((button_state_last & BUTTON_20)) && ((button_state_now & BUTTON_20) == 0) && keyboard.SW21) {
        pitch = G2s;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW21 = 0;
    }
    if(((button_state_last & BUTTON_21)) && ((button_state_now & BUTTON_21) == 0) && keyboard.SW22) {
        pitch = A2;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW22 = 0;
    }
    if(((button_state_last & BUTTON_22)) && ((button_state_now & BUTTON_22) == 0) && keyboard.SW23) {
        pitch = A2s;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW23 = 0;
    }
    if(((button_state_last & BUTTON_23)) && ((button_state_now & BUTTON_23) == 0) && keyboard.SW24) {
        pitch = B2;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW24 = 0;
    }
    if(((button_state_last & BUTTON_24)) && ((button_state_now & BUTTON_24) == 0) && keyboard.SW25) {
        pitch = C3;
        ON_OFF = 0;
        playThisNote(pitch);
        keyboard.SW25 = 0;
    }

}

void playThisNote8(unsigned char pitch, unsigned char index){
    
    unsigned char *mode_p;  //points to a mode

    //selects a mode
    switch (which_mode) {
        case ionian:
            mode_p = ionian_key;
            break;
        case dorian:
            mode_p = dorian_key;
            break;
        case phrygian:
            mode_p = phrygian_key;
            break;
        case lydian:
            mode_p = lydian_key;
            break;
        case mixolydian:
            mode_p = mixolydian_key;
            break;
        case aeolian:
            mode_p = aeolian_key;
            break;
        case locrian:
            mode_p = locrian_key;
            break;
        default:
            break;
    }  
    
    //play major/minor/modes
    if(ARPEGGIO_ON == 0){

        if(KEYBOARD_MODE == MAJOR) {
            if(ON_OFF == 1) {noteOn(channel,major_key[index],velocity);}
            if(ON_OFF == 0) {noteOff(channel,major_key[index],velocity);}
        }
    
        if(KEYBOARD_MODE == MINOR) {
            if(ON_OFF == 1) {noteOn(channel,minor_key[index],velocity);}
            if(ON_OFF == 0) {noteOff(channel,minor_key[index],velocity);}
        }    
    
        if(KEYBOARD_MODE == MODES) {
            if(index == 0) {
                if(ON_OFF == 1) {noteOn(channel,mode_p[index],velocity);}
                if(ON_OFF == 0) {noteOff(channel,mode_p[index],velocity);}
            }
            if(index > 0) {
                if(ON_OFF == 1) {noteOn(channel,mode_p[0] + mode_p[index],velocity);}
                if(ON_OFF == 0) {noteOff(channel,mode_p[0] + mode_p[index],velocity);}
            }        
        }
    }
    
    //play arpeggio of major/minor/modes
    if(ARPEGGIO_ON == 1){
        
        unsigned char temp_pitch;
        
        if(KEYBOARD_MODE == MAJOR) {
            temp_pitch = major_key[index];
        }
    
        if(KEYBOARD_MODE == MINOR) {
           temp_pitch = minor_key[index];
        }
    
        if(KEYBOARD_MODE == MODES) {
            if(index == 0){temp_pitch = mode_p[index];}
            if(index > 0){temp_pitch = (mode_p[0] + mode_p[index]);}
        }

        if(ON_OFF == 1) {
            
            //turn off the timer
            TMR0ON = 0;
            
            parallel = temp_pitch;

            //wait one pulse
            if(NUM_NOTES_PRESSED > 0){            
                wait_one_pulse(LAST_NOTE_MODE_KEY_PRESS);
                if(note_off_was_sent == 0) {key_press_release_note_off();}
                TIMER_OVERFLOWS = 0;
            }

            //add notes to the arpeggio here
            if((KEYBOARD_MODE == MAJOR) | (KEYBOARD_MODE == MINOR) | (KEYBOARD_MODE == MODES)){
                add_notes_to_arpeggio(temp_pitch);
            }            
            
            //for auto-latch
            if(LATCH == 0) {latch_was_pressed = 0;}            

           //finish setting up arpeggio
            finish_arpeggio_setup();            
            
            //turn timer ON
            TMR0ON = 1;
        }
            
        if((ON_OFF == 0) && (LATCH == 0)) {

            //turn off the timer
            TMR0ON = 0;

            //wait one pulse
            if(NUM_NOTES_PRESSED > 0){
                wait_one_pulse(LAST_NOTE_MODE_KEY_RELEASE);
                if(note_off_was_sent == 0) {key_press_release_note_off();}
                TIMER_OVERFLOWS = 0;
            }

            //delete notes from the arpeggio here
            if((KEYBOARD_MODE == MAJOR) | (KEYBOARD_MODE == MINOR) | (KEYBOARD_MODE == MODES)){
                delete_notes_from_arpeggio(temp_pitch);
            }

            if(temp_pitch == parallel){NUM_NOTES_PRESSED = 0;} // changed from 'pitch' to 'temp_pitch'
            
            // 'auto latch' if single key releases and one or more notes are still playing
            // set LATCH = 1 automatically, to keep adding notes to arpeggio (after deleting a note)
            // press UN_LATCH twice and LATCH is set to '0'
            if((AUTO_LATCH == 1) && (latch_was_pressed == 1)){
                LATCH = 1;
            }
            
            //make 2 of these blocks of code (DIATONIC, everything else)
            
            //for single note key presses, un latch mode 'ALL'
            if(((KEYBOARD_MODE == MAJOR) | (KEYBOARD_MODE == MINOR) | (KEYBOARD_MODE == MODES)) && (UN_LATCH_MODE == ALL) && (latch_was_pressed == 1)){
                NUM_NOTES_PRESSED = 0;
                ARRAY_INDEX = 0;
            }
            
            //for diatonic chords, un latch mode 'ALL' OR 'one at a time'
            if((KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) | (KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) | (KEYBOARD_MODE == DIATONIC_7TH_MAJOR) |(KEYBOARD_MODE == DIATONIC_7TH_MINOR) && ((UN_LATCH_MODE == ALL) || (UN_LATCH_MODE == ONE_AT_A_TIME)) && (latch_was_pressed == 1)){
                NUM_NOTES_PRESSED = 0;
                ARRAY_INDEX = 0;
            }

            //finish setting up arpeggio
            finish_arpeggio_setup();
            
            //turn timer ON
            TMR0ON = 1;
        }
    }
    
    if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
        playDiatonicTriadMajor(pitch, index);
    }
    if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
        playDiatonicTriadMinor(pitch, index);
    }
    if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
        playDiatonicSeventhMajor(pitch, index);
    }
    if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
        playDiatonicSeventhMinor(pitch, index);
    }
}

void playDiatonicTriadMajor(unsigned char pitch, unsigned char index) {

    //play chord
    if(ARPEGGIO_ON == 0){
        for(unsigned char i = 0; i<3; i++){
            if(ON_OFF == 1) {noteOn(channel,pitch + diatonic_major[index][i],velocity);}
            if(ON_OFF == 0) {noteOff(channel,pitch + diatonic_major[index][i],velocity);}        
        }
    }
    
    //play arpeggio
    if(ARPEGGIO_ON == 1){
        if(ON_OFF == 1) {
            
            TMR0ON = 0; //added this!
            
            parallel = pitch;
            
            //lets you latch a new chord to arpeggiate
            if(NUM_NOTES_PRESSED > 0){
                wait_one_pulse(LAST_NOTE_MODE_KEY_PRESS);
                if(note_off_was_sent == 0) {key_press_release_note_off();}
                TIMER_OVERFLOWS = 0;
            }            

            for(unsigned char i = 0; i<3; i++){
                ARPEGGIO[i] = pitch + diatonic_major[index][i];
            }
        
            NUM_NOTES_PRESSED = 3;

            //for auto-latch
            if(LATCH == 0) {latch_was_pressed = 0;}
            
            //finish setting up arpeggio
            finish_arpeggio_setup();
            
            TMR0ON = 1;             //start TIMER0
        }
    
        if((ON_OFF == 0) && (LATCH == 0)) {
 
            if(NUM_NOTES_PRESSED > 0){
                wait_one_pulse(LAST_NOTE_MODE_KEY_RELEASE);
                if(note_off_was_sent == 0) {key_press_release_note_off();}
                TIMER_OVERFLOWS = 0;
            }            
            
            if(pitch == parallel){NUM_NOTES_PRESSED = 0;}
            
            if((AUTO_LATCH == 1) && (latch_was_pressed == 1)){
                LATCH = 1;
            }
            
            //changed this to !!!LOGICAL!!!
            //for un-latch
            if(((UN_LATCH_MODE == ALL) || (UN_LATCH_MODE == ONE_AT_A_TIME)) && (latch_was_pressed == 1)){
                NUM_NOTES_PRESSED = 0;
                ARRAY_INDEX = 0;
            } 

            //finish setting up arpeggio
            finish_arpeggio_setup();
            TMR0ON = 1;

        } 
    }
}

void playDiatonicSeventhMajor(unsigned char pitch, unsigned char index) {

    //play chord
    if(ARPEGGIO_ON == 0){    
        for(unsigned char i = 0; i<4; i++){
            //noteOn(channel,triad_p[i] + pitch,velocity);
            if(ON_OFF == 1) {noteOn(channel,pitch + diatonic_seventh_major[index][i],velocity);}
            if(ON_OFF == 0) {noteOff(channel,pitch + diatonic_seventh_major[index][i],velocity);}        
        }    
    }
    
    //play arpeggio
    if(ARPEGGIO_ON == 1){
        if(ON_OFF == 1) {
        
            TMR0ON = 0; //added this!
            
            parallel = pitch;
            
            //lets you latch a new chord to arpeggiate
            if(NUM_NOTES_PRESSED > 0){
                wait_one_pulse(LAST_NOTE_MODE_KEY_PRESS);
                if(note_off_was_sent == 0) {key_press_release_note_off();}
                TIMER_OVERFLOWS = 0;
            }            

            for(unsigned char i = 0; i<4; i++){
                ARPEGGIO[i] = pitch + diatonic_seventh_major[index][i];
            }
        
            NUM_NOTES_PRESSED = 4;

            //for auto-latch
            if(LATCH == 0) {latch_was_pressed = 0;}            
            
            //finish setting up arpeggio
            finish_arpeggio_setup();            
            
            TMR0ON = 1;             //start TIMER0 
            
            return;
        }
    
        if((ON_OFF == 0) && (LATCH == 0)) {

            if(NUM_NOTES_PRESSED > 0){
                wait_one_pulse(LAST_NOTE_MODE_KEY_RELEASE);
                if(note_off_was_sent == 0) {key_press_release_note_off();}
                TIMER_OVERFLOWS = 0;
            }            

            if(pitch == parallel){NUM_NOTES_PRESSED = 0;}
            
            if((AUTO_LATCH == 1) && (latch_was_pressed == 1)){
                LATCH = 1;
            }
            
            //changed this to !!!LOGICAL!!!
            //for un-latch
            if(((UN_LATCH_MODE == ALL || (UN_LATCH_MODE == ONE_AT_A_TIME)) && (latch_was_pressed == 1))){
                NUM_NOTES_PRESSED = 0;
                ARRAY_INDEX = 0;
            }            

            //finish setting up arpeggio
            finish_arpeggio_setup();            
            TMR0ON = 1;
            
            return;
        }
    }
}

void playDiatonicTriadMinor(unsigned char pitch, unsigned char index) {

    //play chord
    if(ARPEGGIO_ON == 0){    
        for(unsigned char i = 0; i<3; i++){
            if(i==0){
                if(ON_OFF == 1) {noteOn(channel,diatonic_minor[index][0],velocity);}
                if(ON_OFF == 0) {noteOff(channel,diatonic_minor[index][0],velocity);}
            }
            if(i>0){
                if(ON_OFF == 1) noteOn(channel,diatonic_minor[index][0] + diatonic_minor[index][i],velocity);
                if(ON_OFF == 0) noteOff(channel,diatonic_minor[index][0] + diatonic_minor[index][i],velocity);
            }
        }
    }
    
    //play arpeggio
    if(ARPEGGIO_ON == 1){    
        if(ON_OFF == 1) {
            
            TMR0ON = 0; //added this!
            
            parallel = pitch;
            
            //lets you latch a new chord to arpeggiate
            if(NUM_NOTES_PRESSED > 0){
                wait_one_pulse(LAST_NOTE_MODE_KEY_PRESS);
                if(note_off_was_sent == 0) {key_press_release_note_off();}
                TIMER_OVERFLOWS = 0;
            }            

            for(unsigned char i = 0; i<3; i++){
                if(i==0){ARPEGGIO[i] = diatonic_minor[index][0];}
                if(i>0){ARPEGGIO[i] = diatonic_minor[index][0] + diatonic_minor[index][i];}
            }
            
            NUM_NOTES_PRESSED = 3;

            //for auto-latch
            if(LATCH == 0) {latch_was_pressed = 0;}
            
            //finish setting up arpeggio
            finish_arpeggio_setup();            
            
            TMR0ON = 1;             //start TIMER0
            
            return;
        }
    
        if((ON_OFF == 0) && (LATCH == 0)) {

            if(NUM_NOTES_PRESSED > 0){
                wait_one_pulse(LAST_NOTE_MODE_KEY_RELEASE);
                if(note_off_was_sent == 0) {key_press_release_note_off();}
                TIMER_OVERFLOWS = 0;
            }            
            
            if(pitch == parallel){NUM_NOTES_PRESSED = 0;}
            
            if((AUTO_LATCH == 1) && (latch_was_pressed == 1)){
                LATCH = 1;
            }
            
            //changed this to !!!LOGICAL!!!
            //for un-latch
            if(((UN_LATCH_MODE == ALL) || (UN_LATCH_MODE == ONE_AT_A_TIME)) && (latch_was_pressed == 1)){
                NUM_NOTES_PRESSED = 0;
                ARRAY_INDEX = 0;
            }          

            //finish setting up arpeggio
            finish_arpeggio_setup();
            TMR0ON = 1;
            
            return;
        }
    }
}

void playDiatonicSeventhMinor(unsigned char pitch, unsigned char index) {

    //play chord
    if(ARPEGGIO_ON == 0){    
        for(unsigned char i = 0; i<4; i++){
            if(i==0){
                if(ON_OFF == 1) {noteOn(channel,diatonic_seventh_minor[index][0],velocity);}
                if(ON_OFF == 0) {noteOff(channel,diatonic_seventh_minor[index][0],velocity);}
            }
            if(i>0){
                if(ON_OFF == 1) noteOn(channel,diatonic_seventh_minor[index][0] + diatonic_seventh_minor[index][i],velocity);
                if(ON_OFF == 0) noteOff(channel,diatonic_seventh_minor[index][0] + diatonic_seventh_minor[index][i],velocity);
            }
        }    
    }

    //play arpeggio
    if(ARPEGGIO_ON == 1){    
    
        if(ON_OFF == 1) {
        
            TMR0ON = 0; //added this!
            
            parallel = pitch;
            
            //lets you latch a new chord to arpeggiate
            if(NUM_NOTES_PRESSED > 0){
                wait_one_pulse(LAST_NOTE_MODE_KEY_PRESS);
                if(note_off_was_sent == 0) {key_press_release_note_off();}
                TIMER_OVERFLOWS = 0;
            }            

            for(unsigned char i = 0; i<4; i++){
                if(i==0){ARPEGGIO[i] = diatonic_seventh_minor[index][0];}
                if(i>0){ARPEGGIO[i] = diatonic_seventh_minor[index][0] + diatonic_seventh_minor[index][i];}
            }
        
            NUM_NOTES_PRESSED = 4;
            
            //for auto-latch
            if(LATCH == 0) {latch_was_pressed = 0;}            
            
            //finish setting up arpeggio
            finish_arpeggio_setup();            
            
            TMR0ON = 1;             //start TIMER0        
        }
    
        if((ON_OFF == 0) && (LATCH == 0)) {

            if(NUM_NOTES_PRESSED > 0){
                wait_one_pulse(LAST_NOTE_MODE_KEY_RELEASE);
                if(note_off_was_sent == 0) {key_press_release_note_off();}
                TIMER_OVERFLOWS = 0;
            }            
            
            if(pitch == parallel){NUM_NOTES_PRESSED = 0;}
            
            if((AUTO_LATCH == 1) && (latch_was_pressed == 1)){
                LATCH = 1;
            }
            
            //changed this to !!!LOGICAL!!!
            //for un-latch
            if(((UN_LATCH_MODE == ALL) | (UN_LATCH_MODE == ONE_AT_A_TIME)) && (latch_was_pressed == 1)){
                NUM_NOTES_PRESSED = 0;
                ARRAY_INDEX = 0;
            }        

            //finish setting up arpeggio
            finish_arpeggio_setup();
            TMR0ON = 1;
            
            return;
        }
    }
}

//eight note keyboard - efficient!
void keyboard_eight_note_efficient(void){
    
    unsigned char pitch;    //is a pitch
    unsigned char index;    //is an array index (different from pitch)
    
    // *** NOTE ON ***
    if((button_state_now & BUTTON_0) && !(button_state_now & BUTTON_27) && !keyboard.SW1){ //!keyboard.SW1
        pitch = C;
        index = 0;
        ON_OFF = 1;
        playThisNote8(pitch, index);
        keyboard.SW1 = 1;
    }
    if((button_state_now & BUTTON_2) && !(button_state_now & BUTTON_27) && !keyboard.SW3){ //!keyboard.SW1
        pitch = D;
        index = 1;
        ON_OFF = 1;        
        playThisNote8(pitch, index);
        keyboard.SW3 = 1;
    }
    if((button_state_now & BUTTON_4) && !(button_state_now & BUTTON_27) && !keyboard.SW5){ //!keyboard.SW1
        pitch = E;
        index = 2;
        ON_OFF = 1;        
        playThisNote8(pitch, index);
        keyboard.SW5 = 5;
    }
   if((button_state_now & BUTTON_5) && !(button_state_now & BUTTON_27) && !keyboard.SW6){ //!keyboard.SW1
        pitch = F;
        index = 3;
        ON_OFF = 1;        
        playThisNote8(pitch, index);
        keyboard.SW6 = 1;
    }
    if((button_state_now & BUTTON_7) && !(button_state_now & BUTTON_27) && !keyboard.SW8){ //!keyboard.SW1
        pitch = G;
        index = 4;
        ON_OFF = 1;        
        playThisNote8(pitch, index);
        keyboard.SW8 = 1;
    }
    if((button_state_now & BUTTON_9) && !(button_state_now & BUTTON_27) && !keyboard.SW10){ //!keyboard.SW1
        pitch = A;
        index = 5;
        ON_OFF = 1;        
        playThisNote8(pitch, index);
        keyboard.SW10 = 1;
    }
    if((button_state_now & BUTTON_11) && !(button_state_now & BUTTON_27) && !keyboard.SW12){ //!keyboard.SW1
        pitch = B;
        index = 6;
        ON_OFF = 1;        
        playThisNote8(pitch, index);
        keyboard.SW12 = 1;
    }
    if((button_state_now & BUTTON_12) && !(button_state_now & BUTTON_27) && !keyboard.SW13){ //!keyboard.SW1
        pitch = C2;
        index = 7;
        ON_OFF = 1;        
        playThisNote8(pitch, index);
        keyboard.SW13 = 1;
    }
    if((button_state_now & BUTTON_14) && !(button_state_now & BUTTON_27) && !keyboard.SW15){ //!keyboard.SW1
        pitch = D2;
        index = 8;
        ON_OFF = 1;
        playThisNote8(pitch, index);
        keyboard.SW15 = 1;
    }
   if((button_state_now & BUTTON_16) && !(button_state_now & BUTTON_27) && !keyboard.SW17){ //!keyboard.SW1
        pitch = E2;
        index = 9;
        ON_OFF = 1;        
        playThisNote8(pitch, index);
        keyboard.SW17 = 1;
    }
    if((button_state_now & BUTTON_17) && !(button_state_now & BUTTON_27) && !keyboard.SW18){ //!keyboard.SW1
        pitch = F2;
        index = 10;
        ON_OFF = 1;        
        playThisNote8(pitch, index);
        keyboard.SW18 = 1;
    }
    if((button_state_now & BUTTON_19) && !(button_state_now & BUTTON_27) && !keyboard.SW20){ //!keyboard.SW1
        pitch = G2;
        index = 11;
        ON_OFF = 1;        
        playThisNote8(pitch, index);
        keyboard.SW20 = 1;
    }
   if((button_state_now & BUTTON_21) && !(button_state_now & BUTTON_27) && !keyboard.SW22){ //!keyboard.SW1
        pitch = A2;
        index = 12;
        ON_OFF = 1;        
        playThisNote8(pitch, index);
        keyboard.SW22 = 1;
    }
    if((button_state_now & BUTTON_23) && !(button_state_now & BUTTON_27) && !keyboard.SW24){ //!keyboard.SW1
        pitch = B2;
        index = 13;
        ON_OFF = 1;        
        playThisNote8(pitch, index);
        keyboard.SW24 = 1;
    }
   if((button_state_now & BUTTON_24) && !(button_state_now & BUTTON_27) && !keyboard.SW25){ //!keyboard.SW1
        pitch = C3;
        index = 14;
        ON_OFF = 1;
        playThisNote8(pitch, index);
        keyboard.SW25 = 1;
    }
    
    // *** NOTE OFF ***
    if(((button_state_last & BUTTON_0)) && ((button_state_now & BUTTON_0) == 0) && keyboard.SW1) {
        pitch = C;
        index = 0;
        ON_OFF = 0;
        playThisNote8(pitch, index);
        keyboard.SW1 = 0;
    }
    if(((button_state_last & BUTTON_2)) && ((button_state_now & BUTTON_2) == 0) && keyboard.SW3) {
        pitch = D;
        index = 1;
        ON_OFF = 0;
        playThisNote8(pitch, index);
        keyboard.SW3 = 0;
    }
    if(((button_state_last & BUTTON_4)) && ((button_state_now & BUTTON_4) == 0) && keyboard.SW5) {
        pitch = E;
        index = 2;
        ON_OFF = 0;
        playThisNote8(pitch, index);
        keyboard.SW5 = 0;
    }
    if(((button_state_last & BUTTON_5)) && ((button_state_now & BUTTON_5) == 0) && keyboard.SW6) {
        pitch = F;
        index = 3;
        ON_OFF = 0;
        playThisNote8(pitch, index);
        keyboard.SW6 = 0;
    }
    if(((button_state_last & BUTTON_7)) && ((button_state_now & BUTTON_7) == 0) && keyboard.SW8) {
        pitch = G;
        index = 4;
        ON_OFF = 0;
        playThisNote8(pitch, index);
        keyboard.SW8 = 0;
    }
    if(((button_state_last & BUTTON_9)) && ((button_state_now & BUTTON_9) == 0) && keyboard.SW10) {
        pitch = A;
        index = 5;
        ON_OFF = 0;
        playThisNote8(pitch, index);
        keyboard.SW10 = 10;
    }
    if(((button_state_last & BUTTON_11)) && ((button_state_now & BUTTON_11) == 0) && keyboard.SW12) {
        pitch = B;
        index = 6;
        ON_OFF = 0;
        playThisNote8(pitch, index);
        keyboard.SW12 = 0;
    }
    if(((button_state_last & BUTTON_12)) && ((button_state_now & BUTTON_12) == 0) && keyboard.SW13) {
        pitch = C2;
        index = 7;
        ON_OFF = 0;
        playThisNote8(pitch, index);
        keyboard.SW13 = 0;
    }
    if(((button_state_last & BUTTON_14)) && ((button_state_now & BUTTON_14) == 0) && keyboard.SW15) {
        pitch = D2;
        index = 8;
        ON_OFF = 0;
        playThisNote8(pitch, index);
        keyboard.SW15 = 0;
    }
    if(((button_state_last & BUTTON_16)) && ((button_state_now & BUTTON_16) == 0) && keyboard.SW17) {
        pitch = E2;
        index = 9;
        ON_OFF = 0;
        playThisNote8(pitch, index);
        keyboard.SW17 = 0;
    }
    if(((button_state_last & BUTTON_17)) && ((button_state_now & BUTTON_17) == 0) && keyboard.SW18) {
        pitch = F2;
        index = 10;
        ON_OFF = 0;
        playThisNote8(pitch, index);
        keyboard.SW18 = 0;
    }
    if(((button_state_last & BUTTON_19)) && ((button_state_now & BUTTON_19) == 0) && keyboard.SW20) {
        pitch = G2;
        index = 11;
        ON_OFF = 0;
        playThisNote8(pitch, index);
        keyboard.SW20 = 0;
    }
    if(((button_state_last & BUTTON_21)) && ((button_state_now & BUTTON_21) == 0) && keyboard.SW22) {
        pitch = A2;
        index = 12;
        ON_OFF = 0;
        playThisNote8(pitch, index);
        keyboard.SW22 = 0;
    }
    if(((button_state_last & BUTTON_23)) && ((button_state_now & BUTTON_23) == 0) && keyboard.SW24) {
        pitch = B2;
        index = 13;
        ON_OFF = 0;
        playThisNote8(pitch, index);
        keyboard.SW24 = 0;
    }
    if(((button_state_last & BUTTON_24)) && ((button_state_now & BUTTON_24) == 0) && keyboard.SW25) {
        pitch = C;
        index = 14;
        ON_OFF = 0;
        playThisNote8(pitch, index);
        keyboard.SW25 = 0;
    }    
}

//entire keyboard
void keyboard_all_note(void) {
    
    unsigned char pitch;        //is a pitch
    
    unsigned char *triad_p;     //points to a triad
    
    //selects a triad type
    switch (which_triad) {
        case major:
            triad_p = major_triad;
            break;
        case minor:
            triad_p = minor_triad;
            break;
        case augmented:
            triad_p = augmented_triad;
            break;
        case diminished:
            triad_p = diminished_triad;
            break;
        default:
            break;
    }
    
    unsigned char *seventh_p;   //points to a seventh chord
    
    //selects a seventh chord type
    switch (which_seventh) {
       case dominant7:
            seventh_p = dominant_7th;
            break;
        case major7:
            seventh_p = major_7th;
            break;
        case minor7:
            seventh_p = minor_7th;
            break;
        case half_diminished7:
            seventh_p = half_diminished_7th;
            break;
        case diminished7:
            seventh_p = diminished_7th;
            break;
        default:
            break;
    }

    
    // !!! SEE IF CODE BELOW CAN BE MADE MORE EFFICIENT !!!
    
    // *** NOTE ON *** POLYPHONIC
    if((button_state_now & BUTTON_0) && !keyboard.SW1){
        pitch = C;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0],velocity);
            noteOn(channel,triad_p[1],velocity);
            noteOn(channel,triad_p[2],velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0],velocity);
            noteOn(channel,seventh_p[1],velocity);
            noteOn(channel,seventh_p[2],velocity);
            noteOn(channel,seventh_p[3],velocity);
        }
        keyboard.SW1 = 1;
    }
    if((button_state_now & BUTTON_1) && !keyboard.SW2) {
        pitch = Cs;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }    
        keyboard.SW2 = 1;
    }
    if((button_state_now & BUTTON_2) && !keyboard.SW3) {
        pitch = D;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
       keyboard.SW3 = 1;
    }
    if((button_state_now & BUTTON_3) && !keyboard.SW4) {
        pitch = Ds;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW4 = 1;
    }
    if((button_state_now & BUTTON_4) && !keyboard.SW5) {
        pitch = E;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW5 = 1;
    }
    if((button_state_now & BUTTON_5) && !keyboard.SW6) {
        pitch = F;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW6 = 1;
    }
    if((button_state_now & BUTTON_6) && !keyboard.SW7) {
        pitch = Fs;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW7 = 1;
    }
    if((button_state_now & BUTTON_7) && !keyboard.SW8) {
        pitch = G;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW8 = 1;
    }
    if((button_state_now & BUTTON_8) && !keyboard.SW9) {
        pitch = Gs;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW9 = 1;
    }
    if((button_state_now & BUTTON_9) && !keyboard.SW10) {
        pitch = A;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW10 = 1;
    }
    if((button_state_now & BUTTON_10) && !keyboard.SW11) {
        pitch = As;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW11 = 1;
    }
    if((button_state_now & BUTTON_11) && !keyboard.SW12) {
        pitch = B;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW12 = 1;
    }
    if((button_state_now & BUTTON_12) && !keyboard.SW13) {
        pitch = C2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW13 = 1;
    }
    
    //!!! PASTE 2ND OCTAVE HERE (NOTE ON) !!!
    
    if((button_state_now & BUTTON_13) && !keyboard.SW14){
        pitch = C2s;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0],velocity);
            noteOn(channel,triad_p[1],velocity);
            noteOn(channel,triad_p[2],velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0],velocity);
            noteOn(channel,seventh_p[1],velocity);
            noteOn(channel,seventh_p[2],velocity);
            noteOn(channel,seventh_p[3],velocity);
        }
        keyboard.SW14 = 1;
    }
    if((button_state_now & BUTTON_14) && !keyboard.SW15) {
        pitch = D2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }    
        keyboard.SW15 = 1;
    }
    if((button_state_now & BUTTON_15) && !keyboard.SW16) {
        pitch = D2s;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
       keyboard.SW16 = 1;
    }
    if((button_state_now & BUTTON_16) && !keyboard.SW17) {
        pitch = E2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW17 = 1;
    }
    if((button_state_now & BUTTON_17) && !keyboard.SW18) {
        pitch = F2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW18 = 1;
    }
    if((button_state_now & BUTTON_18) && !keyboard.SW19) {
        pitch = F2s;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW19 = 1;
    }
    if((button_state_now & BUTTON_19) && !keyboard.SW20) {
        pitch = G2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW20 = 1;
    }
    if((button_state_now & BUTTON_20) && !keyboard.SW21) {
        pitch = G2s;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW21 = 1;
    }
    if((button_state_now & BUTTON_21) && !keyboard.SW22) {
        pitch = A2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW22 = 1;
    }
    if((button_state_now & BUTTON_22) && !keyboard.SW23) {
        pitch = A2s;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW23 = 1;
    }
    if((button_state_now & BUTTON_23) && !keyboard.SW24) {
        pitch = B2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW24 = 1;
    }
    if((button_state_now & BUTTON_24) && !keyboard.SW25) {
        pitch = C3;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW25 = 1;
    }
    
    // !!! END OF PASTE !!!
 
    // *** NOTE OFF *** POLYPHONIC
    if(((button_state_last & BUTTON_0)) && ((button_state_now & BUTTON_0) == 0) && keyboard.SW1) {
        pitch = C;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0],velocity);
            noteOff(channel,triad_p[1],velocity);
            noteOff(channel,triad_p[2],velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                  
        keyboard.SW1 = 0;
    }
    if(((button_state_last & BUTTON_1)) && ((button_state_now & BUTTON_1) == 0) && keyboard.SW2) {
        pitch = Cs;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW2 = 0;
    }
    if(((button_state_last & BUTTON_2)) && ((button_state_now & BUTTON_2) == 0) && keyboard.SW3) {
        pitch = D;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW3 = 0;
    }
    if(((button_state_last & BUTTON_3)) && ((button_state_now & BUTTON_3) == 0) && keyboard.SW4) {
        pitch = Ds;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW4 = 0;
    }
    if(((button_state_last & BUTTON_4)) && ((button_state_now & BUTTON_4) == 0) && keyboard.SW5) {
        pitch = E;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW5 = 0;
    }
    if(((button_state_last & BUTTON_5)) && ((button_state_now & BUTTON_5) == 0) && keyboard.SW6) {
        pitch = F;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW6 = 0;
    }
    if(((button_state_last & BUTTON_6)) && ((button_state_now & BUTTON_6) == 0) && keyboard.SW7) {
        pitch = Fs;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW7 = 0;
    }
    if(((button_state_last & BUTTON_7)) && ((button_state_now & BUTTON_7) == 0) && keyboard.SW8) {
        pitch = G;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW8 = 0;
    }
    if(((button_state_last & BUTTON_8)) && ((button_state_now & BUTTON_8) == 0) && keyboard.SW9) {
        pitch = Gs;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW9 = 0;
    }
    if(((button_state_last & BUTTON_9)) && ((button_state_now & BUTTON_9) == 0) && keyboard.SW10) {
        pitch = A;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW10 = 0;
    }
    if(((button_state_last & BUTTON_10)) && ((button_state_now & BUTTON_10) == 0) && keyboard.SW11) {
        pitch = As;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW11 = 0;
    }
    if(((button_state_last & BUTTON_11)) && ((button_state_now & BUTTON_11) == 0) && keyboard.SW12) {
        pitch = B;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW12 = 0;
    }
    if(((button_state_last & BUTTON_12)) && ((button_state_now & BUTTON_12) == 0) && keyboard.SW13) {
        pitch = C2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW13 = 0;
    }
    
    //!!! PASTE 2ND OCTAVE HERE (NOTE OFF) !!!
    
    if(((button_state_last & BUTTON_13)) && ((button_state_now & BUTTON_13) == 0) && keyboard.SW14) {
        pitch = C2s;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0],velocity);
            noteOff(channel,triad_p[1],velocity);
            noteOff(channel,triad_p[2],velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                  
        keyboard.SW14 = 0;
    }
    if(((button_state_last & BUTTON_14)) && ((button_state_now & BUTTON_14) == 0) && keyboard.SW15) {
        pitch = D2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW15 = 0;
    }
    if(((button_state_last & BUTTON_15)) && ((button_state_now & BUTTON_15) == 0) && keyboard.SW16) {
        pitch = D2s;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW16 = 0;
    }
    if(((button_state_last & BUTTON_16)) && ((button_state_now & BUTTON_16) == 0) && keyboard.SW17) {
        pitch = E2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW17 = 0;
    }
    if(((button_state_last & BUTTON_17)) && ((button_state_now & BUTTON_17) == 0) && keyboard.SW18) {
        pitch = F2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW18 = 0;
    }
    if(((button_state_last & BUTTON_18)) && ((button_state_now & BUTTON_18) == 0) && keyboard.SW19) {
        pitch = F2s;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW19 = 0;
    }
    if(((button_state_last & BUTTON_19)) && ((button_state_now & BUTTON_19) == 0) && keyboard.SW20) {
        pitch = G2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW20 = 0;
    }
    if(((button_state_last & BUTTON_20)) && ((button_state_now & BUTTON_20) == 0) && keyboard.SW21) {
        pitch = G2s;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW21 = 0;
    }
    if(((button_state_last & BUTTON_21)) && ((button_state_now & BUTTON_21) == 0) && keyboard.SW22) {
        pitch = A2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW22 = 0;
    }
    if(((button_state_last & BUTTON_22)) && ((button_state_now & BUTTON_22) == 0) && keyboard.SW23) {
        pitch = A2s;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW23 = 0;
    }
    if(((button_state_last & BUTTON_23)) && ((button_state_now & BUTTON_23) == 0) && keyboard.SW24) {
        pitch = B2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW24 = 0;
    }
    if(((button_state_last & BUTTON_24)) && ((button_state_now & BUTTON_24) == 0) && keyboard.SW25) {
        pitch = C3;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW25 = 0;
    }
    
    // !!! END OF PASTE !!!
}

//white keys only
void keyboard_eight_note(void) {
    
    unsigned char pitch;    //is a pitch
    
    unsigned char *mode_p;  //points to a mode
    
    //selects a mode
    switch (which_mode) {
        case ionian:
            mode_p = ionian_key;
            break;
        case dorian:
            mode_p = dorian_key;
            break;
        case phrygian:
            mode_p = phrygian_key;
            break;
        case lydian:
            mode_p = lydian_key;
            break;
        case mixolydian:
            mode_p = mixolydian_key;
            break;
        case aeolian:
            mode_p = aeolian_key;
            break;
        case locrian:
            mode_p = locrian_key;
            break;
        default:
            break;
    }

    // *** NOTE ON ***
    if((button_state_now & BUTTON_0) && !keyboard.SW1){ //!keyboard.SW1
        pitch = C;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[0],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[0],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[0][0],velocity);
            noteOn(channel,pitch + diatonic_major[0][1],velocity);
            noteOn(channel,pitch + diatonic_major[0][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[0][0],velocity);
            noteOn(channel,diatonic_minor[0][0] + diatonic_minor[0][1],velocity);
            noteOn(channel,diatonic_minor[0][0] + diatonic_minor[0][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[0][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[0][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[0][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[0][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[0][0],velocity);
            noteOn(channel,diatonic_seventh_minor[0][0] + diatonic_seventh_minor[0][1],velocity);
            noteOn(channel,diatonic_seventh_minor[0][0] + diatonic_seventh_minor[0][2],velocity);
            noteOn(channel,diatonic_seventh_minor[0][0] + diatonic_seventh_minor[0][3],velocity);
        }
        keyboard.SW1 = 1;
    }
    if((button_state_now & BUTTON_2) && !keyboard.SW3) {
        pitch = D;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[1],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[1],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[1],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[1][0],velocity);
            noteOn(channel,pitch + diatonic_major[1][1],velocity);
            noteOn(channel,pitch + diatonic_major[1][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[1][0],velocity);
            noteOn(channel,diatonic_minor[1][0] + diatonic_minor[1][1],velocity);
            noteOn(channel,diatonic_minor[1][0] + diatonic_minor[1][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[1][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[1][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[1][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[1][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[1][0],velocity);
            noteOn(channel,diatonic_seventh_minor[1][0] + diatonic_seventh_minor[1][1],velocity);
            noteOn(channel,diatonic_seventh_minor[1][0] + diatonic_seventh_minor[1][2],velocity);
            noteOn(channel,diatonic_seventh_minor[1][0] + diatonic_seventh_minor[1][3],velocity);
        }        
        keyboard.SW3 = 1;
    }
    if((button_state_now & BUTTON_4) && !keyboard.SW5) {
        pitch = E;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[2],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[2],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[2],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[2][0],velocity);
            noteOn(channel,pitch + diatonic_major[2][1],velocity);
            noteOn(channel,pitch + diatonic_major[2][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[2][0],velocity);
            noteOn(channel,diatonic_minor[2][0] + diatonic_minor[2][1],velocity);
            noteOn(channel,diatonic_minor[2][0] + diatonic_minor[2][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[2][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[2][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[2][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[2][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[2][0],velocity);
            noteOn(channel,diatonic_seventh_minor[2][0] + diatonic_seventh_minor[2][1],velocity);
            noteOn(channel,diatonic_seventh_minor[2][0] + diatonic_seventh_minor[2][2],velocity);
            noteOn(channel,diatonic_seventh_minor[2][0] + diatonic_seventh_minor[2][3],velocity);
        }                
        keyboard.SW5 = 1;    
    }              
    if((button_state_now & BUTTON_5) && !keyboard.SW6) {
        pitch = F;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[3],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[3],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[3],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[3][0],velocity);
            noteOn(channel,pitch + diatonic_major[3][1],velocity);
            noteOn(channel,pitch + diatonic_major[3][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[3][0],velocity);
            noteOn(channel,diatonic_minor[3][0] + diatonic_minor[3][1],velocity);
            noteOn(channel,diatonic_minor[3][0] + diatonic_minor[3][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[3][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[3][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[3][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[3][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[3][0],velocity);
            noteOn(channel,diatonic_seventh_minor[3][0] + diatonic_seventh_minor[3][1],velocity);
            noteOn(channel,diatonic_seventh_minor[3][0] + diatonic_seventh_minor[3][2],velocity);
            noteOn(channel,diatonic_seventh_minor[3][0] + diatonic_seventh_minor[3][3],velocity);
        }                
        keyboard.SW6 = 1;
    }
    if((button_state_now & BUTTON_7) && !keyboard.SW8) {
        pitch = G;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[4],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[4],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[4],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[4][0],velocity);
            noteOn(channel,pitch + diatonic_major[4][1],velocity);
            noteOn(channel,pitch + diatonic_major[4][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[4][0],velocity);
            noteOn(channel,diatonic_minor[4][0] + diatonic_minor[4][1],velocity);
            noteOn(channel,diatonic_minor[4][0] + diatonic_minor[4][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[4][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[4][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[4][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[4][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[4][0],velocity);
            noteOn(channel,diatonic_seventh_minor[4][0] + diatonic_seventh_minor[4][1],velocity);
            noteOn(channel,diatonic_seventh_minor[4][0] + diatonic_seventh_minor[4][2],velocity);
            noteOn(channel,diatonic_seventh_minor[4][0] + diatonic_seventh_minor[4][3],velocity);
        }                
        keyboard.SW8 = 1;
    }
    if((button_state_now & BUTTON_9) && !keyboard.SW10) {
        pitch = A;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[5],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[5],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[5],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[5][0],velocity);
            noteOn(channel,pitch + diatonic_major[5][1],velocity);
            noteOn(channel,pitch + diatonic_major[5][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[5][0],velocity);
            noteOn(channel,diatonic_minor[5][0] + diatonic_minor[5][1],velocity);
            noteOn(channel,diatonic_minor[5][0] + diatonic_minor[5][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[5][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[5][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[5][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[5][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[5][0],velocity);
            noteOn(channel,diatonic_seventh_minor[5][0] + diatonic_seventh_minor[5][1],velocity);
            noteOn(channel,diatonic_seventh_minor[5][0] + diatonic_seventh_minor[5][2],velocity);
            noteOn(channel,diatonic_seventh_minor[5][0] + diatonic_seventh_minor[5][3],velocity);
        }                
        keyboard.SW10 = 1;
    }
    if((button_state_now & BUTTON_11) && !keyboard.SW12) {
        pitch = B;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[6],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[6],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[6],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[6][0],velocity);
            noteOn(channel,pitch + diatonic_major[6][1],velocity);
            noteOn(channel,pitch + diatonic_major[6][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[6][0],velocity);
            noteOn(channel,diatonic_minor[6][0] + diatonic_minor[6][1],velocity);
            noteOn(channel,diatonic_minor[6][0] + diatonic_minor[6][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[6][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[6][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[6][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[6][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[6][0],velocity);
            noteOn(channel,diatonic_seventh_minor[6][0] + diatonic_seventh_minor[6][1],velocity);
            noteOn(channel,diatonic_seventh_minor[6][0] + diatonic_seventh_minor[6][2],velocity);
            noteOn(channel,diatonic_seventh_minor[6][0] + diatonic_seventh_minor[6][3],velocity);
        }                
        keyboard.SW12 = 1;
    }
    if((button_state_now & BUTTON_12) && !keyboard.SW13) {
        pitch = C2;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[7],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[7],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[7],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[7][0],velocity);
            noteOn(channel,pitch + diatonic_major[7][1],velocity);
            noteOn(channel,pitch + diatonic_major[7][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[7][0],velocity);
            noteOn(channel,diatonic_minor[7][0] + diatonic_minor[7][1],velocity);
            noteOn(channel,diatonic_minor[7][0] + diatonic_minor[7][2],velocity);
            //noteOn(channel,diatonic_minor[7][1],velocity);
            //noteOn(channel,diatonic_minor[7][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[7][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[7][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[7][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[7][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[7][0],velocity);
            noteOn(channel,diatonic_seventh_minor[7][0] + diatonic_seventh_minor[7][1],velocity);
            noteOn(channel,diatonic_seventh_minor[7][0] + diatonic_seventh_minor[7][2],velocity);
            noteOn(channel,diatonic_seventh_minor[7][0] + diatonic_seventh_minor[7][3],velocity);
        }         
        keyboard.SW13 = 1;
    }
 
    //!!! PASTE 2ND OCTAVE HERE (NOTE ON) !!!
    
    if((button_state_now & BUTTON_14) && !keyboard.SW15){ //!keyboard.SW1
        pitch = D2;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[8],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[8],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[8],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[8][0],velocity);
            noteOn(channel,pitch + diatonic_major[8][1],velocity);
            noteOn(channel,pitch + diatonic_major[8][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[8][0],velocity);
            //noteOn(channel,diatonic_minor[8][1],velocity);
            //noteOn(channel,diatonic_minor[8][2],velocity);
            noteOn(channel,diatonic_minor[8][0] + diatonic_minor[8][1],velocity);
            noteOn(channel,diatonic_minor[8][0] + diatonic_minor[8][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[8][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[8][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[8][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[8][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[8][0],velocity);
            noteOn(channel,diatonic_seventh_minor[8][0] + diatonic_seventh_minor[8][1],velocity);
            noteOn(channel,diatonic_seventh_minor[8][0] + diatonic_seventh_minor[8][2],velocity);
            noteOn(channel,diatonic_seventh_minor[8][0] + diatonic_seventh_minor[8][3],velocity);
        }
        keyboard.SW15 = 1;
    }
    if((button_state_now & BUTTON_16) && !keyboard.SW17) {
        pitch = E2;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[9],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[9],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[9],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[9][0],velocity);
            noteOn(channel,pitch + diatonic_major[9][1],velocity);
            noteOn(channel,pitch + diatonic_major[9][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[9][0],velocity);
            //noteOn(channel,diatonic_minor[9][1],velocity);
            //noteOn(channel,diatonic_minor[9][2],velocity);
            noteOn(channel,diatonic_minor[9][0] + diatonic_minor[9][1],velocity);
            noteOn(channel,diatonic_minor[9][0] + diatonic_minor[9][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[9][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[9][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[9][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[9][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[9][0],velocity);
            noteOn(channel,diatonic_seventh_minor[9][0] + diatonic_seventh_minor[9][1],velocity);
            noteOn(channel,diatonic_seventh_minor[9][0] + diatonic_seventh_minor[9][2],velocity);
            noteOn(channel,diatonic_seventh_minor[9][0] + diatonic_seventh_minor[9][3],velocity);
        }        
        keyboard.SW17 = 1;
    }
    if((button_state_now & BUTTON_17) && !keyboard.SW18) {
        pitch = F2;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[10],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[10],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[10],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[10][0],velocity);
            noteOn(channel,pitch + diatonic_major[10][1],velocity);
            noteOn(channel,pitch + diatonic_major[10][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[10][0],velocity);
            //noteOn(channel,diatonic_minor[10][1],velocity);
            //noteOn(channel,diatonic_minor[10][2],velocity);
            noteOn(channel,diatonic_minor[10][0] + diatonic_minor[10][1],velocity);
            noteOn(channel,diatonic_minor[10][0] + diatonic_minor[10][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[10][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[10][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[10][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[10][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[10][0],velocity);
            noteOn(channel,diatonic_seventh_minor[10][0] + diatonic_seventh_minor[10][1],velocity);
            noteOn(channel,diatonic_seventh_minor[10][0] + diatonic_seventh_minor[10][2],velocity);
            noteOn(channel,diatonic_seventh_minor[10][0] + diatonic_seventh_minor[10][3],velocity);
        }                
        keyboard.SW18 = 1;    
    }              
    if((button_state_now & BUTTON_19) && !keyboard.SW20) {
        pitch = G2;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[11],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[11],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[11],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[11][0],velocity);
            noteOn(channel,pitch + diatonic_major[11][1],velocity);
            noteOn(channel,pitch + diatonic_major[11][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[11][0],velocity);
            //noteOn(channel,diatonic_minor[11][1],velocity);
            //noteOn(channel,diatonic_minor[11][2],velocity);
            noteOn(channel,diatonic_minor[11][0] + diatonic_minor[11][1],velocity);
            noteOn(channel,diatonic_minor[11][0] + diatonic_minor[11][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[11][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[11][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[11][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[11][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[11][0],velocity);
            noteOn(channel,diatonic_seventh_minor[11][0] + diatonic_seventh_minor[11][1],velocity);
            noteOn(channel,diatonic_seventh_minor[11][0] + diatonic_seventh_minor[11][2],velocity);
            noteOn(channel,diatonic_seventh_minor[11][0] + diatonic_seventh_minor[11][3],velocity);
        }                
        keyboard.SW20 = 1;
    }
    if((button_state_now & BUTTON_21) && !keyboard.SW22) {
        pitch = A2;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[12],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[12],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[12],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[12][0],velocity);
            noteOn(channel,pitch + diatonic_major[12][1],velocity);
            noteOn(channel,pitch + diatonic_major[12][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[12][0],velocity);
            //noteOn(channel,diatonic_minor[12][1],velocity);
            //noteOn(channel,diatonic_minor[12][2],velocity);
            noteOn(channel,diatonic_minor[12][0] + diatonic_minor[12][1],velocity);
            noteOn(channel,diatonic_minor[12][0] + diatonic_minor[12][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[12][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[12][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[12][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[12][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[12][0],velocity);
            noteOn(channel,diatonic_seventh_minor[12][0] + diatonic_seventh_minor[12][1],velocity);
            noteOn(channel,diatonic_seventh_minor[12][0] + diatonic_seventh_minor[12][2],velocity);
            noteOn(channel,diatonic_seventh_minor[12][0] + diatonic_seventh_minor[12][3],velocity);
        }                
        keyboard.SW22 = 1;
    }
    if((button_state_now & BUTTON_23) && !keyboard.SW24) {
        pitch = B2;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[13],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[13],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[13],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[13][0],velocity);
            noteOn(channel,pitch + diatonic_major[13][1],velocity);
            noteOn(channel,pitch + diatonic_major[13][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[13][0],velocity);
            //noteOn(channel,diatonic_minor[13][1],velocity);
            //noteOn(channel,diatonic_minor[13][2],velocity);
            noteOn(channel,diatonic_minor[13][0] + diatonic_minor[13][1],velocity);
            noteOn(channel,diatonic_minor[13][0] + diatonic_minor[13][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[13][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[13][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[13][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[13][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[13][0],velocity);
            noteOn(channel,diatonic_seventh_minor[13][0] + diatonic_seventh_minor[13][1],velocity);
            noteOn(channel,diatonic_seventh_minor[13][0] + diatonic_seventh_minor[13][2],velocity);
            noteOn(channel,diatonic_seventh_minor[13][0] + diatonic_seventh_minor[13][3],velocity);
        }                
        keyboard.SW24 = 1;
    }

    if((button_state_now & BUTTON_24) && !keyboard.SW25) {
        pitch = C3;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[14],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[14],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[14],velocity);}
        keyboard.SW25 = 1;
    }    
    
    // !!! END OF PASTE !!!
    
    // *** NOTE OFF ***
    if(((button_state_last & BUTTON_0)) && ((button_state_now & BUTTON_0) == 0) && keyboard.SW1) {
        pitch = C;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[0],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[0],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,diatonic_major[0][0],velocity);
            noteOff(channel,diatonic_major[0][1],velocity);
            noteOff(channel,diatonic_major[0][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[0][0],velocity);
            noteOff(channel,diatonic_minor[0][0] + diatonic_minor[0][1],velocity);
            noteOff(channel,diatonic_minor[0][0] + diatonic_minor[0][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[0][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[0][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[0][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[0][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[0][0],velocity);
            noteOff(channel,diatonic_seventh_minor[0][0] + diatonic_seventh_minor[0][1],velocity);
            noteOff(channel,diatonic_seventh_minor[0][0] + diatonic_seventh_minor[0][2],velocity);
            noteOff(channel,diatonic_seventh_minor[0][0] + diatonic_seventh_minor[0][3],velocity);
        }        
        keyboard.SW1 = 0;
    }
    if(((button_state_last & BUTTON_2)) && ((button_state_now & BUTTON_2) == 0) && keyboard.SW3) {
        pitch = D;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[1],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[1],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[1],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[1][0],velocity);
            noteOff(channel,pitch + diatonic_major[1][1],velocity);
            noteOff(channel,pitch + diatonic_major[1][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[1][0],velocity);
            noteOff(channel,diatonic_minor[1][0] + diatonic_minor[1][1],velocity);
            noteOff(channel,diatonic_minor[1][0] + diatonic_minor[1][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[1][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[1][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[1][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[1][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[1][0],velocity);
            noteOff(channel,diatonic_seventh_minor[1][0] + diatonic_seventh_minor[1][1],velocity);
            noteOff(channel,diatonic_seventh_minor[1][0] + diatonic_seventh_minor[1][2],velocity);
            noteOff(channel,diatonic_seventh_minor[1][0] + diatonic_seventh_minor[1][3],velocity);
        }        
        keyboard.SW3 = 0;
    }
    if(((button_state_last & BUTTON_4)) && ((button_state_now & BUTTON_4) == 0) && keyboard.SW5) {
        pitch = E;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[2],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[2],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[2],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[2][0],velocity);
            noteOff(channel,pitch + diatonic_major[2][1],velocity);
            noteOff(channel,pitch + diatonic_major[2][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[2][0],velocity);
            noteOff(channel,diatonic_minor[2][0] + diatonic_minor[2][1],velocity);
            noteOff(channel,diatonic_minor[2][0] + diatonic_minor[2][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[2][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[2][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[2][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[2][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[2][0],velocity);
            noteOff(channel,diatonic_seventh_minor[2][0] + diatonic_seventh_minor[2][1],velocity);
            noteOff(channel,diatonic_seventh_minor[2][0] + diatonic_seventh_minor[2][2],velocity);
            noteOff(channel,diatonic_seventh_minor[2][0] + diatonic_seventh_minor[2][3],velocity);
        }        
        keyboard.SW5 = 0;
    }
    if(((button_state_last & BUTTON_5)) && ((button_state_now & BUTTON_5) == 0) && keyboard.SW6) {
        pitch = F;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[3],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[3],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[3],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[3][0],velocity);
            noteOff(channel,pitch + diatonic_major[3][1],velocity);
            noteOff(channel,pitch + diatonic_major[3][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[3][0],velocity);
            noteOff(channel,diatonic_minor[3][0] + diatonic_minor[3][1],velocity);
            noteOff(channel,diatonic_minor[3][0] + diatonic_minor[3][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[3][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[3][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[3][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[3][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[3][0],velocity);
            noteOff(channel,diatonic_seventh_minor[3][0] + diatonic_seventh_minor[3][1],velocity);
            noteOff(channel,diatonic_seventh_minor[3][0] + diatonic_seventh_minor[3][2],velocity);
            noteOff(channel,diatonic_seventh_minor[3][0] + diatonic_seventh_minor[3][3],velocity);
        }        
        keyboard.SW6 = 0;
    }
    if(((button_state_last & BUTTON_7)) && ((button_state_now & BUTTON_7) == 0) && keyboard.SW8) {
        pitch = G;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[4],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[4],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[4],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[4][0],velocity);
            noteOff(channel,pitch + diatonic_major[4][1],velocity);
            noteOff(channel,pitch + diatonic_major[4][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[4][0],velocity);
            noteOff(channel,diatonic_minor[4][0] + diatonic_minor[4][1],velocity);
            noteOff(channel,diatonic_minor[4][0] + diatonic_minor[4][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[4][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[4][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[4][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[4][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[4][0],velocity);
            noteOff(channel,diatonic_seventh_minor[4][0] + diatonic_seventh_minor[4][1],velocity);
            noteOff(channel,diatonic_seventh_minor[4][0] + diatonic_seventh_minor[4][2],velocity);
            noteOff(channel,diatonic_seventh_minor[4][0] + diatonic_seventh_minor[4][3],velocity);
        }        
        keyboard.SW8 = 0;
    }
    if(((button_state_last & BUTTON_9)) && ((button_state_now & BUTTON_9) == 0) && keyboard.SW10) {
        pitch = A;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[5],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[5],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[5],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[5][0],velocity);
            noteOff(channel,pitch + diatonic_major[5][1],velocity);
            noteOff(channel,pitch + diatonic_major[5][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[5][0],velocity);
            noteOff(channel,diatonic_minor[5][0] + diatonic_minor[5][1],velocity);
            noteOff(channel,diatonic_minor[5][0] + diatonic_minor[5][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[5][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[5][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[5][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[5][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[5][0],velocity);
            noteOff(channel,diatonic_seventh_minor[5][0] + diatonic_seventh_minor[5][1],velocity);
            noteOff(channel,diatonic_seventh_minor[5][0] + diatonic_seventh_minor[5][2],velocity);
            noteOff(channel,diatonic_seventh_minor[5][0] + diatonic_seventh_minor[5][3],velocity);
        }        
        keyboard.SW10 = 0;
    }
    if(((button_state_last & BUTTON_11)) && ((button_state_now & BUTTON_11) == 0) && keyboard.SW12) {
        pitch = B;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[6],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[6],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[6],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[6][0],velocity);
            noteOff(channel,pitch + diatonic_major[6][1],velocity);
            noteOff(channel,pitch + diatonic_major[6][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[6][0],velocity);
            noteOff(channel,diatonic_minor[6][0] + diatonic_minor[6][1],velocity);
            noteOff(channel,diatonic_minor[6][0] + diatonic_minor[6][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[6][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[6][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[6][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[6][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[6][0],velocity);
            noteOff(channel,diatonic_seventh_minor[6][0] + diatonic_seventh_minor[6][1],velocity);
            noteOff(channel,diatonic_seventh_minor[6][0] + diatonic_seventh_minor[6][2],velocity);
            noteOff(channel,diatonic_seventh_minor[6][0] + diatonic_seventh_minor[6][3],velocity);
        }        
        keyboard.SW12 = 0;
    }
    
    if(((button_state_last & BUTTON_12)) && ((button_state_now & BUTTON_12) == 0) && keyboard.SW13) {
        pitch = C2;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[7],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[7],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[7],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[7][0],velocity);
            noteOff(channel,pitch + diatonic_major[7][1],velocity);
            noteOff(channel,pitch + diatonic_major[7][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[7][0],velocity);
            noteOff(channel,diatonic_minor[7][0] + diatonic_minor[7][1],velocity);
            noteOff(channel,diatonic_minor[7][0] + diatonic_minor[7][2],velocity);
            //noteOff(channel,diatonic_minor[7][1],velocity);
            //noteOff(channel,diatonic_minor[7][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[7][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[7][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[7][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[7][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[7][0],velocity);
            noteOff(channel,diatonic_seventh_minor[7][0] + diatonic_seventh_minor[7][1],velocity);
            noteOff(channel,diatonic_seventh_minor[7][0] + diatonic_seventh_minor[7][2],velocity);
            noteOff(channel,diatonic_seventh_minor[7][0] + diatonic_seventh_minor[7][3],velocity);
        }         
        keyboard.SW13 = 0;
    }
    
    //!!! PASTE 2ND OCTAVE HERE (NOTE ON) !!!

    if(((button_state_last & BUTTON_14)) && ((button_state_now & BUTTON_14) == 0) && keyboard.SW15) {
        pitch = D2;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[8],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[8],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[8],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[8][0],velocity);
            noteOff(channel,pitch + diatonic_major[8][1],velocity);
            noteOff(channel,pitch + diatonic_major[8][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[8][0],velocity);
            //noteOff(channel,diatonic_minor[8][1],velocity);
            //noteOff(channel,diatonic_minor[8][2],velocity);
            noteOff(channel,diatonic_minor[8][0] + diatonic_minor[8][1],velocity);
            noteOff(channel,diatonic_minor[8][0] + diatonic_minor[8][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[8][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[8][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[8][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[8][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[8][0],velocity);
            noteOff(channel,diatonic_seventh_minor[8][0] + diatonic_seventh_minor[8][1],velocity);
            noteOff(channel,diatonic_seventh_minor[8][0] + diatonic_seventh_minor[8][2],velocity);
            noteOff(channel,diatonic_seventh_minor[8][0] + diatonic_seventh_minor[8][3],velocity);
        }
        keyboard.SW15 = 0;
    }
    
    if(((button_state_last & BUTTON_16)) && ((button_state_now & BUTTON_16) == 0) && keyboard.SW17) {
        pitch = E2;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[9],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[9],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[9],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[9][0],velocity);
            noteOff(channel,pitch + diatonic_major[9][1],velocity);
            noteOff(channel,pitch + diatonic_major[9][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[9][0],velocity);
            //noteOff(channel,diatonic_minor[9][1],velocity);
            //noteOff(channel,diatonic_minor[9][2],velocity);
            noteOff(channel,diatonic_minor[9][0] + diatonic_minor[9][1],velocity);
            noteOff(channel,diatonic_minor[9][0] + diatonic_minor[9][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[9][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[9][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[9][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[9][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[9][0],velocity);
            noteOff(channel,diatonic_seventh_minor[9][0] + diatonic_seventh_minor[9][1],velocity);
            noteOff(channel,diatonic_seventh_minor[9][0] + diatonic_seventh_minor[9][2],velocity);
            noteOff(channel,diatonic_seventh_minor[9][0] + diatonic_seventh_minor[9][3],velocity);
        }        
        keyboard.SW17 = 0;
    }
    if(((button_state_last & BUTTON_17)) && ((button_state_now & BUTTON_17) == 0) && keyboard.SW18) {
        pitch = F2;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[10],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[10],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[10],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[10][0],velocity);
            noteOff(channel,pitch + diatonic_major[10][1],velocity);
            noteOff(channel,pitch + diatonic_major[10][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[10][0],velocity);
            //noteOff(channel,diatonic_minor[10][1],velocity);
            //noteOff(channel,diatonic_minor[10][2],velocity);
            noteOff(channel,diatonic_minor[10][0] + diatonic_minor[10][1],velocity);
            noteOff(channel,diatonic_minor[10][0] + diatonic_minor[10][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[10][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[10][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[10][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[10][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[10][0],velocity);
            noteOff(channel,diatonic_seventh_minor[10][0] + diatonic_seventh_minor[10][1],velocity);
            noteOff(channel,diatonic_seventh_minor[10][0] + diatonic_seventh_minor[10][2],velocity);
            noteOff(channel,diatonic_seventh_minor[10][0] + diatonic_seventh_minor[10][3],velocity);
        }                
        keyboard.SW18 = 0;    
    }              
    if(((button_state_last & BUTTON_19)) && ((button_state_now & BUTTON_19) == 0) && keyboard.SW20) {
        pitch = G2;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[11],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[11],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[11],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[11][0],velocity);
            noteOff(channel,pitch + diatonic_major[11][1],velocity);
            noteOff(channel,pitch + diatonic_major[11][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[11][0],velocity);
            //noteOff(channel,diatonic_minor[11][1],velocity);
            //noteOff(channel,diatonic_minor[11][2],velocity);
            noteOff(channel,diatonic_minor[11][0] + diatonic_minor[11][1],velocity);
            noteOff(channel,diatonic_minor[11][0] + diatonic_minor[11][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[11][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[11][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[11][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[11][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[11][0],velocity);
            noteOff(channel,diatonic_seventh_minor[11][0] + diatonic_seventh_minor[11][1],velocity);
            noteOff(channel,diatonic_seventh_minor[11][0] + diatonic_seventh_minor[11][2],velocity);
            noteOff(channel,diatonic_seventh_minor[11][0] + diatonic_seventh_minor[11][3],velocity);
        }                
        keyboard.SW20 = 0;
    }
    if(((button_state_last & BUTTON_21)) && ((button_state_now & BUTTON_21) == 0) && keyboard.SW22) {
        pitch = A2;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[12],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[12],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[12],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[12][0],velocity);
            noteOff(channel,pitch + diatonic_major[12][1],velocity);
            noteOff(channel,pitch + diatonic_major[12][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[12][0],velocity);
            //noteOff(channel,diatonic_minor[12][1],velocity);
            //noteOff(channel,diatonic_minor[12][2],velocity);
            noteOff(channel,diatonic_minor[12][0] + diatonic_minor[12][1],velocity);
            noteOff(channel,diatonic_minor[12][0] + diatonic_minor[12][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[12][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[12][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[12][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[12][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[124][0],velocity);
            noteOff(channel,diatonic_seventh_minor[12][0] + diatonic_seventh_minor[12][1],velocity);
            noteOff(channel,diatonic_seventh_minor[12][0] + diatonic_seventh_minor[12][2],velocity);
            noteOff(channel,diatonic_seventh_minor[12][0] + diatonic_seventh_minor[12][3],velocity);
        }                
        keyboard.SW22 = 0;
    }
    if(((button_state_last & BUTTON_23)) && ((button_state_now & BUTTON_23) == 0) && keyboard.SW24) {
        pitch = B2;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[13],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[13],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[13],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[13][0],velocity);
            noteOff(channel,pitch + diatonic_major[13][1],velocity);
            noteOff(channel,pitch + diatonic_major[13][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[13][0],velocity);
            //noteOff(channel,diatonic_minor[13][1],velocity);
            //noteOff(channel,diatonic_minor[13][2],velocity);
            noteOff(channel,diatonic_minor[13][0] + diatonic_minor[13][1],velocity);
            noteOff(channel,diatonic_minor[13][0] + diatonic_minor[13][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[13][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[13][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[13][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[13][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[13][0],velocity);
            noteOff(channel,diatonic_seventh_minor[13][0] + diatonic_seventh_minor[13][1],velocity);
            noteOff(channel,diatonic_seventh_minor[13][0] + diatonic_seventh_minor[13][2],velocity);
            noteOff(channel,diatonic_seventh_minor[13][0] + diatonic_seventh_minor[13][3],velocity);
        }                
        keyboard.SW24 = 0;
    }

    if(((button_state_last & BUTTON_24)) && ((button_state_now & BUTTON_24) == 0) && keyboard.SW25) {
        pitch = C3;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[14],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[14],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[14],velocity);}
        keyboard.SW25 = 0;
    }    
    

    // !!! END OF PASTE !!!
}
