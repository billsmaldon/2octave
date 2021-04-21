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

#include "encoder.h"

//read encoder bits
void encoderInputsBuxton(void) {
    unsigned char pinstate = PORTB & 0b00110000;
    pinstate = (pinstate >> 4);
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
    }
    
    encoder_direction = DIR_NONE;
    
}
