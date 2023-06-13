/*  The code of encoder.c and encoder.h is a derivative work of the code from
    Buxtronix, which is licensed GPL v3. This code therefore is also licensed
    under the terms of the GNU Public License, version 3.
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

#include "encoder.h"

//read encoder bits
void encoderInputsBuxton(void) {

    //for CW is increase
    if(encoderPolarity == 0){
        encoderA = RB5;
        encoderB = RB4;
    }
    
    //for CCW is increase
    if(encoderPolarity == 1){
        encoderA = RB4;
        encoderB = RB5;
    }
    
    //new version of reading pinstate
    unsigned char tempA = encoderA << 1;
    unsigned char tempB = encoderB;
    unsigned char pinstate = tempA | tempB;
    
    state = ttable[state & 0xf][pinstate]; // Determine new state from the pins and state table.
    encoder_direction = state & 0x30;  // Return emit bits, ie the generated event.
}

//process encoder bits
void processEncoderBuxton(void) {
    
    if (encoder_direction == DIR_NONE) {return;}

    //increase variable here
    if (encoder_direction == DIR_CW) {
        
        lcd_print_once = 0; //update the LCD

        //selector bits for all MENU items
        if (which_screen == MAIN_MENU) {
            if(mainMenu.selector < mainMenu.number - 1){    
                mainMenu.selector++;
            }
        }
        if (which_screen == KEYBOARD_MENU) {
            if(keyboardMenu.selector < (keyboardMenu.number - 1)){
                keyboardMenu.selector++;
            }
        }
        if (which_screen == TRANSPOSE_MENU) {
            if(transposeMenu.selector < (transposeMenu.number - 1)){
                transposeMenu.selector++;
            }
        }
        if (which_screen == DRUM_MENU) {
            if(drumMenu.selector < (drumMenu.number - 1)){
                drumMenu.selector++;
            }
        }
        if (which_screen == POTENTIOMETER_MENU) {
            if(potsMenu.selector < (potsMenu.number - 1)){
                potsMenu.selector++;
            }
        }
        if (which_screen == MIDI_CHANNEL_MENU) {
            if(midiChannelMenu.selector < (midiChannelMenu.number - 1)){
                midiChannelMenu.selector++;
            }                    
        }

        if (which_screen == MODES_MENU) {
            if(modeMenu.selector < (modeMenu.number - 1)){
                modeMenu.selector++;
            }
        }
        if (which_screen == TRIADS_MENU) {
            if(triadMenu.selector < (triadMenu.number - 1)){
                triadMenu.selector++;
            }
        }
        if (which_screen == SEVENTHS_MENU) {
            if(seventhMenu.selector < (seventhMenu.number - 1)){
                seventhMenu.selector++;
            }
        }
        if (which_screen == DRUMS_CC_TYPE_MENU) {
            if(drumCCTypeMenu.selector < (drumCCTypeMenu.number - 1)){
                drumCCTypeMenu.selector++;
            }
        }
        //DRUMS_NN_MENU
        if (which_screen == DRUMS_NN_MENU) {
            if(drumNNMenu.selector < (drumNNMenu.number - 1)){
                drumNNMenu.selector++;
            }
        }        
        //DRUMS_CC_MENU
        if (which_screen == DRUMS_CC_MENU) {
            if(drumCCMenu.selector < (drumCCMenu.number - 1)){
                drumCCMenu.selector++;
            }
        }
        //POTS_RESO_MENU
        if (which_screen == POTS_RES_MENU) {
            if(potsResoMenu.selector < (potsResoMenu.number - 1)){
                potsResoMenu.selector++;
            }
        }
        //ENCODER_POLARITY_MENU
        if (which_screen == ENCODER_POLARITY_MENU) {
            //if(encoderPolarityMenu.selector < (encoderPolarityMenu.number - 1)){
            //    encoderPolarityMenu.selector++;
            //}
            if(encoderPolarityMenu.selector == 0){
                encoderPolarityMenu.selector = 1;
            }            
        }        
        //POTS_ALPHA_MENU
        if (which_screen == POTS_ALPHA_MENU) {
            if(potsAlphaMenu.selector <= 85){
                potsAlphaMenu.selector += 5;
            }
        }        
        //POTS_CC_MENU
        if (which_screen == POTS_CC_MENU) {
            if(potsCCMenu.selector < (potsCCMenu.number - 1)){
                potsCCMenu.selector++;
            }
        }
        //SLIDEPOTS_CC_MENU
        if (which_screen == SLIDEPOTS_CC_MENU) {
            if(slidepotsCCMenu.selector < (slidepotsCCMenu.number - 1)){
                slidepotsCCMenu.selector++;
            }
        }
        
        if (which_screen == PROGRAM_CHANGE_MENU) {
            if(programChangeMenu.selector < 127){
                programChangeMenu.selector++;
            }            
        }
        
        if (which_screen == MAIN_CH_MENU) {
            if(mainChannelMenu.selector < 15){
                mainChannelMenu.selector++;
            }            
        }
        
        if (which_screen == DRUM_CH_MENU) {
            if(drumChannelMenu.selector < 15){
                drumChannelMenu.selector++;
            }            
        }
        if (which_screen == JOYSTICK_CC_MENU) {
            if(joystickCCMenu.selector < (joystickCCMenu.number - 1)){
                joystickCCMenu.selector++;
            }            
        }        
        if (which_screen == EEPROM_MENU) {
            if(eepromMenu.selector < (eepromMenu.number - 1)){
                eepromMenu.selector++;
            }            
        }              
        if (which_screen == SAVES_MENU) {
            if(savesMenu.selector < (savesMenu.number - 1)){
                savesMenu.selector++;
            }            
        }           
        
        if (which_screen == ARPEGGIATOR_MENU) {
            if(arpeggiatorMenu.selector < (arpeggiatorMenu.number - 1)){
                arpeggiatorMenu.selector++;
            }               
        }
        
        if (which_screen == ARPEGGIATOR_ON_OFF_MENU) {
            arpeggiatorOnOffMenu.selector ^= 1;
            //if(arpeggiatorOnOffMenu.selector == 0){
            //    arpeggiatorOnOffMenu.selector = 1;
            //}
        }
        if (which_screen == ARPEGGIATOR_TEMPO_MENU) {
            if(arpeggiatorTempoMenu.selector < 250){
                arpeggiatorTempoMenu.selector++;
            }               
        }
        if (which_screen == ARPEGGIATOR_OCTAVES_MENU) {
            if(arpeggiatorOctavesMenu.selector < 4){
                arpeggiatorOctavesMenu.selector++;
            }               
        }
        if (which_screen == ARPEGGIATOR_ARPEGGIO_TYPE_MENU) {
            if(arpeggiatorTypeMenu.selector < (arpeggiatorTypeMenu.number - 1)){
                arpeggiatorTypeMenu.selector++;
            }               
        }
        if (which_screen == ARPEGGIATOR_NOTE_LENGTH_MENU) {
            if(arpeggiatorNoteLengthMenu.selector < (arpeggiatorNoteLengthMenu.number - 1)){
                arpeggiatorNoteLengthMenu.selector++;
            }               
        }        
        if (which_screen == ARPEGGIATOR_LATCH_MENU) {
            //arpeggiatorLatchMenu.selector ^= 1;
            if(arpeggiatorLatchMenu.selector < (arpeggiatorLatchMenu.number - 1)){
                arpeggiatorLatchMenu.selector++;
            }               
        }
        if (which_screen == ARPEGGIATOR_LATCH_ON_OFF_MENU) {
            arpeggiatorLatchOnOffMenu.selector ^= 1;
        }
        if (which_screen == ARPEGGIATOR_AUTO_LATCH_ON_OFF_MENU) {
            arpeggiatorAutoLatchOnOffMenu.selector ^= 1;
        }
        if (which_screen == ARPEGGIATOR_UN_LATCH_MODE_MENU) {
            arpeggiatorUnLatchModeMenu.selector ^= 1;
        }
        if (which_screen == ARPEGGIATOR_RANDOMIZE_SKIP_MENU) {
            if(arpeggiatorRandomizeSkipMenu.selector < (arpeggiatorRandomizeSkipMenu.number - 1)){
                arpeggiatorRandomizeSkipMenu.selector++;
            }               
        }
        if (which_screen == ARPEGGIATOR_RANDOMIZE_TYPE_MENU) {
            arpeggiatorRandomizeTypeMenu.selector ^= 1;
            //if(arpeggiatorRandomizeTypeMenu.selector < (arpeggiatorRandomizeTypeMenu.number - 1)){
            //    arpeggiatorRandomizeTypeMenu.selector++;
            //}               
        }
        if (which_screen == ARPEGGIATOR_SKIP_FIRST_LAST_MENU) {
            arpeggiatorSkipFirstLastMenu.selector ^= 1;
        }
        if (which_screen == ARPEGGIATOR_LAST_NOTE_MODE_MENU) {
            if(arpeggiatorLastNoteModeMenu.selector < (arpeggiatorLastNoteModeMenu.number - 1)){
                arpeggiatorLastNoteModeMenu.selector++;
            }               
        }
        if (which_screen == ARPEGGIATOR_LAST_NOTE_MODE_KEY_PRESS_MENU) {
            arpeggiatorLastNoteModeKeyPressMenu.selector ^= 1;
        }
        if (which_screen == ARPEGGIATOR_LAST_NOTE_MODE_KEY_RELEASE_MENU) {
            arpeggiatorLastNoteModeKeyReleaseMenu.selector ^= 1;
        }
        if (which_screen == ARPEGGIATOR_LAST_NOTE_MODE_TRANSPOSE_MENU) {
            arpeggiatorLastNoteModeTransposeMenu.selector ^= 1;
        }
        if (which_screen == ARPEGGIATOR_LAST_NOTE_MODE_RESET_MENU) {
            arpeggiatorLastNoteModeResetMenu.selector ^= 1;
        }
    }

    //decrease variable here
    if (encoder_direction == DIR_CCW) {

        lcd_print_once = 0; //update the LCD
        
        //selector bits for all MENU items
        if (which_screen == MAIN_MENU) {
            if(mainMenu.selector > 0){
                mainMenu.selector--;
            }
        }
        if (which_screen == KEYBOARD_MENU) {
            if(keyboardMenu.selector > 0){
                keyboardMenu.selector--;
            }
        }
        if (which_screen == TRANSPOSE_MENU) {
            if(transposeMenu.selector > 0){
                transposeMenu.selector--;
            }
        }
        if (which_screen == DRUM_MENU) {
            if(drumMenu.selector > 0){
                drumMenu.selector--;
            }
        }
        if (which_screen == POTENTIOMETER_MENU) {
            if(potsMenu.selector > 0){
                potsMenu.selector--;
            }
        }
        if (which_screen == MIDI_CHANNEL_MENU) {
            if(midiChannelMenu.selector > 0){
                midiChannelMenu.selector--;
            }                    
        }
        
        if (which_screen == MODES_MENU) {
            if(modeMenu.selector > 0){
                modeMenu.selector--;
            }
        }    

        if (which_screen == TRIADS_MENU) {
            if(triadMenu.selector > 0){
                triadMenu.selector--;
            }
        }
        if (which_screen == SEVENTHS_MENU) {
            if(seventhMenu.selector > 0){
                seventhMenu.selector--;
            }
        }
        if (which_screen == DRUMS_CC_TYPE_MENU) {
            if(drumCCTypeMenu.selector > 0){
                drumCCTypeMenu.selector--;
            }
        }
        //DRUMS_NN_MENU
        if (which_screen == DRUMS_NN_MENU) {
            if(drumNNMenu.selector > 0){
                drumNNMenu.selector--;
            }
        }        
        //DRUMS_CC_MENU
        if (which_screen == DRUMS_CC_MENU) {
            if(drumCCMenu.selector > 0){
                drumCCMenu.selector--;
            }
        }
        //POTS_RESO_MENU
        if (which_screen == POTS_RES_MENU) {
            if(potsResoMenu.selector > 0){
                potsResoMenu.selector--;
            }
        }
        //ENCODER_POLARITY_MENU
        if (which_screen == ENCODER_POLARITY_MENU) {
            if(encoderPolarityMenu.selector == 1){
                encoderPolarityMenu.selector = 0;
            }
        }        
        //POTS_ALPHA_MENU
        if (which_screen == POTS_ALPHA_MENU) {
            if(potsAlphaMenu.selector >= 15){
                potsAlphaMenu.selector -= 5;
            }
        }        
        //POTS_CC_MENU
        if (which_screen == POTS_CC_MENU) {
            if(potsCCMenu.selector > -2){
                potsCCMenu.selector--;
            }
        }
        //SLIDEPOTS_CC_MENU
        if (which_screen == SLIDEPOTS_CC_MENU) {
            if(slidepotsCCMenu.selector > -2){
                slidepotsCCMenu.selector--;
            }
        }
        if (which_screen == PROGRAM_CHANGE_MENU) {
            if(programChangeMenu.selector > 0){
                programChangeMenu.selector--;
            }            
        }
        
        if (which_screen == MAIN_CH_MENU) {
            if(mainChannelMenu.selector > 0){
                mainChannelMenu.selector--;
            }            
        }
        
        if (which_screen == DRUM_CH_MENU) {
            if(drumChannelMenu.selector > 0){
                drumChannelMenu.selector--;
            }            
        }

        if (which_screen == JOYSTICK_CC_MENU) {
            if(joystickCCMenu.selector > -2){
                joystickCCMenu.selector--;
            }
        }
        if (which_screen == EEPROM_MENU) {
            if(eepromMenu.selector > 0){
                eepromMenu.selector--;
            }
        }
        if (which_screen == SAVES_MENU) {
            if(savesMenu.selector > 0){
                savesMenu.selector--;
            }
        }
        if (which_screen == ARPEGGIATOR_MENU) {
            if(arpeggiatorMenu.selector > 0){
                arpeggiatorMenu.selector--;
            }
        }
        if (which_screen == ARPEGGIATOR_ON_OFF_MENU) {
            arpeggiatorOnOffMenu.selector ^= 1;
            //if(arpeggiatorOnOffMenu.selector == 1){
            //    arpeggiatorOnOffMenu.selector = 0;
            //}
        }
        if (which_screen == ARPEGGIATOR_TEMPO_MENU) {
            if(arpeggiatorTempoMenu.selector > 25){
                arpeggiatorTempoMenu.selector--;
            }
        }
        if (which_screen == ARPEGGIATOR_OCTAVES_MENU) {
            if(arpeggiatorOctavesMenu.selector > 1){
                arpeggiatorOctavesMenu.selector--;
            }
        }         
        if (which_screen == ARPEGGIATOR_ARPEGGIO_TYPE_MENU) {
            if(arpeggiatorTypeMenu.selector > 0){
                arpeggiatorTypeMenu.selector--;
            }               
        }
        if (which_screen == ARPEGGIATOR_NOTE_LENGTH_MENU) {
            if(arpeggiatorNoteLengthMenu.selector > 0){
                arpeggiatorNoteLengthMenu.selector--;
            }               
        }            
        if (which_screen == ARPEGGIATOR_LATCH_MENU) {
            //arpeggiatorLatchMenu.selector ^= 1;
            if(arpeggiatorLatchMenu.selector > 0){
                arpeggiatorLatchMenu.selector--;
            }               
        }
        if (which_screen == ARPEGGIATOR_LATCH_ON_OFF_MENU) {
            arpeggiatorLatchOnOffMenu.selector ^= 1;
        }
        if (which_screen == ARPEGGIATOR_AUTO_LATCH_ON_OFF_MENU) {
            arpeggiatorAutoLatchOnOffMenu.selector ^= 1;
        }          
        if (which_screen == ARPEGGIATOR_UN_LATCH_MODE_MENU) {
            arpeggiatorUnLatchModeMenu.selector ^= 1;
        }
        if (which_screen == ARPEGGIATOR_RANDOMIZE_SKIP_MENU) {
            if(arpeggiatorRandomizeSkipMenu.selector > 0){
                arpeggiatorRandomizeSkipMenu.selector--;
            }               
        }
        if (which_screen == ARPEGGIATOR_RANDOMIZE_TYPE_MENU) {
            arpeggiatorRandomizeTypeMenu.selector ^= 1;
            //if(arpeggiatorRandomizeTypeMenu.selector > 0){
            //    arpeggiatorRandomizeTypeMenu.selector--;
            //}               
        }
        if (which_screen == ARPEGGIATOR_SKIP_FIRST_LAST_MENU) {
            arpeggiatorSkipFirstLastMenu.selector ^= 1;
        }
        if (which_screen == ARPEGGIATOR_LAST_NOTE_MODE_MENU) {
            if(arpeggiatorLastNoteModeMenu.selector > 0){
                arpeggiatorLastNoteModeMenu.selector--;
            }               
        }
        if (which_screen == ARPEGGIATOR_LAST_NOTE_MODE_KEY_PRESS_MENU) {
            arpeggiatorLastNoteModeKeyPressMenu.selector ^= 1;
        }
        if (which_screen == ARPEGGIATOR_LAST_NOTE_MODE_KEY_RELEASE_MENU) {
            arpeggiatorLastNoteModeKeyReleaseMenu.selector ^= 1;
        }
        if (which_screen == ARPEGGIATOR_LAST_NOTE_MODE_TRANSPOSE_MENU) {
            arpeggiatorLastNoteModeTransposeMenu.selector ^= 1;
        } 
        if (which_screen == ARPEGGIATOR_LAST_NOTE_MODE_TRANSPOSE_MENU) {
            arpeggiatorLastNoteModeTransposeMenu.selector ^= 1;
        }
        if (which_screen == ARPEGGIATOR_LAST_NOTE_MODE_RESET_MENU) {
            arpeggiatorLastNoteModeResetMenu.selector ^= 1;
        }
    }
    
    encoder_direction = DIR_NONE;
    
}
