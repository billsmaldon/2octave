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

#ifndef ASCII_H_INCLUDED
#define ASCII_H_INCLUDED

// !!! HERE ARE ALL THE USER INTERFACE DISPLAY STRINGS !!!
static const unsigned char LCD_STRINGS[][17] = {
    
    //main menu strings
    {"KEYBOARD MODE:"},     //keyboard settings
    {"ARPEGGIO MENU:"},     //arpeggio menu         //moved from last main menu to after KEYBOARD MODE
    {"TRANSPOSE MODE:"},    //transpose settings
    {"DRUM MODE:"},         //drum button settings
    {"POTS MODE:"},         //potentiometer settings
    {"MIDI CHANNELS:"},     //midi channel settings
    {"PROGRAM CHANGE:"},    //midi program change
    {"EEPROM MENU:"},       //eeprom
    
    //keyboard mode strings
    {"CHROMATIC"},  //chromatic scale
    {"MAJOR"},      //major scale
    {"MINOR"},      //minor scale
    {"MODES"},      //modes                             //NEEDS SUB-MENU
    {"PENTATONIC MAJOR"}, //pentatonic scale menu
    {"PENTATONIC MINOR"}, //pentatonic scale menu
    {"TRIAD"},      //triads (chords)                   //NEEDS SUB-MENU
    {"DIATONIC T MAJOR"},   //diatonic major triads
    {"DIATONIC T MINOR"},   //diatonic minor triads
    {"SEVENTH"},            //seventh chords            //NEEDS SUB-MENU
    {"DIATONIC 7 MAJOR"},   //diatonic major seventh chords
    {"DIATONIC 7 MINOR"},   //diatonic minor seventh chords
    
    //which mode strings
    {"ionian"},
    {"dorian"},
    {"phrygian"},
    {"lydian"},
    {"mixolydian"},
    {"aeolian"},
    {"locrian"},

    //which triad strings
    {"major triad"},
    {"minor triad"},
    {"augmented triad"},
    {"diminished triad"},
    
    //which seventh strings
    {"dominant 7th"},
    {"major 7th"},
    {"minor 7th"},
    {"half diminished"},
    {"diminished 7th"},
    
    //transpose mode strings
    {"HALF STEP"}, //transpose by +/-1 semitone
    {"CIRCLE OF FIFTHS"}, //transpose by +/- 7 semitones
    
    //drum mode strings
    {"DRUM IS NOTE ON"},//drum button plays note on
    {"DRUM IS CC"},     //drum button triggers control change
    {"DRUM CC TYPE"},   //select mode for control change buttons
    {"DRUM SET NN#"},
    {"DRUM SET CC#"},
    
    //drum cc type strings
    {"DRUM CC TRIGGER"},          //control change is trigger
    {"DRUM CC TOGGLE"},           //control change is toggle    
    
    //drum note numbers and control change numbers
    {"DRUM 1 NN: "},        //DRUM 1-8 NOTE NUMBER
    {"DRUM 2 NN: "},        //DRUM 1-8 NOTE NUMBER
    {"DRUM 3 NN: "},        //DRUM 1-8 NOTE NUMBER
    {"DRUM 4 NN: "},        //DRUM 1-8 NOTE NUMBER
    {"DRUM 5 NN: "},        //DRUM 1-8 NOTE NUMBER
    {"DRUM 6 NN: "},        //DRUM 1-8 NOTE NUMBER
    {"DRUM 7 NN: "},        //DRUM 1-8 NOTE NUMBER
    {"DRUM 8 NN: "},        //DRUM 1-8 NOTE NUMBER    
        
    {"DRUM 1 CC: "},        //DRUM 1-8 CONTROL CHANGE NUMBER
    {"DRUM 2 CC: "},        //DRUM 1-8 CONTROL CHANGE NUMBER
    {"DRUM 3 CC: "},        //DRUM 1-8 CONTROL CHANGE NUMBER
    {"DRUM 4 CC: "},        //DRUM 1-8 CONTROL CHANGE NUMBER
    {"DRUM 5 CC: "},        //DRUM 1-8 CONTROL CHANGE NUMBER
    {"DRUM 6 CC: "},        //DRUM 1-8 CONTROL CHANGE NUMBER
    {"DRUM 7 CC: "},        //DRUM 1-8 CONTROL CHANGE NUMBER
    {"DRUM 8 CC: "},        //DRUM 1-8 CONTROL CHANGE NUMBER    
    
    //potentiometer menu
    {"POTS RESOLUTION"},    //set potentiometer resolution
    {"POTS ALPHA"},         //set potentiometer alpha
    {"POTS SET CC#"},       //potentiometers control change numbers
    {"SLIDEPOT SET CC#"},   //slide potentiometers control change numbers
    {"JOYSTICK SET CC#"},   //joystick control change numbers

    //potentiometer resolution
    {"POTS LO RES"},       //POTENTIOMETERS ARE 7 BIT MODE
    {"POTS HI RES"},       //POTENTIOMETERS ARE 17 BIT MODE
    
    //potentiometer control change numbers
    {"P1 CC:" },       //POTENTIOMETER 1-7 CONTROL CHANGE NUMBER
    {"P2 CC:" },       //POTENTIOMETER 1-7 CONTROL CHANGE NUMBER
    {"P3 CC:" },       //POTENTIOMETER 1-7 CONTROL CHANGE NUMBER
    {"P4 CC:" },       //POTENTIOMETER 1-7 CONTROL CHANGE NUMBER
    {"P5 CC:" },       //POTENTIOMETER 1-7 CONTROL CHANGE NUMBER
    {"P6 CC:" },       //POTENTIOMETER 1-7 CONTROL CHANGE NUMBER
    {"P7 CC:" },       //POTENTIOMETER 1-7 CONTROL CHANGE NUMBER

    //slide potentiometer control change numbers
    {"S1 CC: "},       //SLIDE POTENTIOMETER 1-7 CONTROL CHANGE NUMBER
    {"S2 CC: "},       //SLIDE POTENTIOMETER 1-7 CONTROL CHANGE NUMBER
    {"S3 CC: "},       //SLIDE POTENTIOMETER 1-7 CONTROL CHANGE NUMBER
    {"S4 CC: "},       //SLIDE POTENTIOMETER 1-7 CONTROL CHANGE NUMBER
    {"S5 CC: "},       //SLIDE POTENTIOMETER 1-7 CONTROL CHANGE NUMBER    
    {"S6 CC: "},       //SLIDE POTENTIOMETER 1-7 CONTROL CHANGE NUMBER    
    {"S7 CC: "},       //SLIDE POTENTIOMETER 1-7 CONTROL CHANGE NUMBER    
    
    //joystick control change numbers
    {"JX CC: "},       //JOYSTICK X AXIS CONTROL CHANGE NUMBER
    {"JY CC: "},       //JOYSTICK Y AXIS CONTROL CHANGE NUMBER    
    
    //midi channels
    {"Main channel"},
    {"Drum channel"},
    
    //save to/load from eeprom
    {"Save settings"},
    {"Load settings"},
    {"Restore defaults"},
    {"Encoder Polarity"},
    {"Exit"},
    
    //save/load slots
    {"Slot 1"},
    {"Slot 2"},
    {"Slot 3"},
    {"Slot 4"},
    {"Exit"},
    
    //encoder polarity strings
    {"CW IS INCREASE"},       //ebay encoder
    {"CCW IS INCREASE"},      //digikey encoder
    
    //ARPEGGIO MENU: strings
    {"Arpeggio OFF/ON"},

    //tempo
    {"Tempo"},                     // 25-250 BPM
                                    //unsigned char BPM = 25; //the tempo
                                    //TIMER_PRELOAD = calculate_pulse_length();
    
    //octaves
    {"Octave Range"},              // 1-4 OCTAVES
                                    //unsigned char OCTAVES = 3;    
    
    //arpeggiator type strings
    {"Arpeggio Type"},
                                    //set up arpeggio with ENUM
                                    //then call setupArpeggio();
    
    //note length strings
    {"Note Length"},    
    //latch arpeggio
    {"Latch/Auto Latch"},
    //un-latch arpeggio
    {"Un-latch Mode"},    
    //random, shuffle, skip
    {"Randomize/Skip"},
    //last note mode
    {"Last Note Mode"},    
    
    //OFF/ON
    {"ARPEGGIATOR OFF"},
    {"ARPEGGIATOR ON"},

    {"UP"},
    {"DOWN"},
    {"UP/DOWN"},
    {"DOWN/UP"},
    {"SHUFFLE"},
    {"RANDOM"},    
    {"AS PRESSED"},
    
    //note length strings
    //unsigned char NOTE_LENGTH_PULSES = QUARTER;   //set note length with ENUM
    //unsigned char NOTE_LENGTH_PULSES_ARRAY[12]    //set note length with ARRAY
    {"1/4"},
    {"1/4 DOTTED"},
    {"1/4 TRIPLET"},
    
    {"1/8"},
    {"1/8 DOTTED"},
    {"1/8 TRIPLET"},
    
    {"1/16"},
    {"1/16 DOTTED"},
    {"1/16 TRIPLET"},
    
    {"1/32"},
    {"1/32 DOTTED"},
    {"1/32 TRIPLET"},      
    
    //latch
    {"SET/CLEAR LATCH"},//either OFF or ON
    {"AUTO LATCH"},     //either OFF or ON

    //un-latch mode
    {"Un-Latch Mode"},
    {"UNLATCH ALL"},
    {"ONE AT A TIME"},

    //randomize, shuffle and skip first/last
    {"Randomize"},
    {"Skip First/Last"},
    
    //randomize type strings
    {"RANDOMIZE AUTO"},
    {"RANDOMIZE ONCE"},

    //lastNoteMode strings
    {"Key press"},
    {"Key release"},
    {"Transpose"},
    {"Reset"},

    //arpeggio reset settings - not implemented
    //{"RESET ON PRESS"},
    //{"RESET ON RELEASE"},
    
    //display NUM_NOTES_PRESSED and 'which_note + 1'
    //DISPLAY_STEP_NUMBER - not implemented
};

//strings total size
//const unsigned char menu_items_lcd_total = sizeof(LCD_STRINGS) / sizeof(LCD_STRINGS[0]);

#endif