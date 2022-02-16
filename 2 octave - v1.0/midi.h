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

#ifndef MIDI_H_INCLUDED
#define MIDI_H_INCLUDED

#include <xc.h>
#define _XTAL_FREQ 20000000

//for transmit to teensy
#define clockPin RA5
#define dataPin RE2
#define messageReady RB2

//MIDI TRANSMIT CHANNELS
unsigned char channel = 0x00;
unsigned char drumchannel = 0x09;

//USART transmit one byte
void sendOut (unsigned char a );
//note off - main channel
void noteOff (unsigned char channel, unsigned char pitch, unsigned char velocity);
//note on - main channel
void noteOn (unsigned char channel, unsigned char pitch, unsigned char velocity);
//note off - drum channel
void noteOffDrum (unsigned char channel, unsigned char pitch, unsigned char velocity);
//note on - drum channel
void noteOnDrum (unsigned char channel, unsigned char pitch, unsigned char velocity);
//transmit a control change
void controlChange (unsigned char channel, unsigned char controllerNumber, unsigned char value);
//transmit a pitch bend
void pitchBend (unsigned char channel, unsigned char lowByte,  unsigned char highByte);
//transmit a program change
void programChange (unsigned char channel, unsigned char data1,  unsigned char data2);

//enum of status byte command numbers
enum statusByteCommand {
    note_on = 0x90,
    note_off = 0x80,
    key_pressure = 0xA0,
    control_change = 0xB0,
    program_change = 0xC0,
    channel_pressure = 0xD0,
    pitch_bend = 0xE0,
    system_msg = 0xF0 // ???
};

//MIDI MESSAGE VARIABLES
unsigned char command = note_off;       //default command is note off
unsigned char statusByte = 0x00;        //clear statusByte
unsigned char noteNumber = 0x00;        //clear noteNumber (data1)
unsigned char velocity = 127;           //set velocity to 127 (data2)
unsigned char patch_number = 0;         //set program change to 0
signed char octave = 4;               //defaults to octave 4 for middle C
signed char semitone = 0;               //semitone transpose (is signed char!)

//enum of controller numbers
enum controllerNumber{
    
    // *** 14 bit controls ***
    // 0-31 (MSB), 32-63 (LSB)
    
    //use signed char to extend controller number range
    velocity_controller_number = -1,
    pitch_bend_controller_number = -2,
    modulation_wheel_controller_number = -3,
    
    program_change_MSB = 0,
    modulation_wheel_MSB = 1,
    volume_MSB = 7,
    
    program_change_LSB = 32,
    modulation_wheel_LSB = 33,
    volume_LSB = 39,    

    // CC# 2-11 don't use
    
    // CC# 12-21
    effect_control_1 = 12,
    effect_control_2 = 13,
    
    knob_1_MSB = 16,
    
    knob_1_LSB = 48, // temporary!
    
    knob_2_MSB = 17,        
    knob_3_MSB = 18,
    knob_4_MSB = 19,
    
    //20-31 undefined
    // can use this range!
    knob_5_MSB = 20,
    knob_6_MSB = 21,
    knob_7_MSB = 22,

    slider_1_MSB = 23,
    slider_2_MSB = 24,
    slider_3_MSB = 25,
    slider_4_MSB = 26,         
    slider_5_MSB = 27,
    slider_6_MSB = 28,
    slider_7_MSB = 29,
  
    general_purpose_controller_1_LSB = 48,
    general_purpose_controller_2_LSB = 49,        
    general_purpose_controller_3_LSB = 50,
    general_purpose_controller_4_LSB = 51,
    
    // *** 7 bit controls ***

    //64-69 switches

    //70-79 sound controller 1-10
    knob_1 = 70,
    knob_2 = 71,
    knob_3 = 72,
    knob_4 = 73,
    knob_5 = 74,
    knob_6 = 75,
    knob_7 = 76,
    
    //80-83 generic on/off switch    
    button_1 = 80,
    button_2 = 81,
    button_3 = 82,
    button_4 = 83,
    
    //84 portamento    
    portamento_amount = 84,
    
    //85-90 undefined
    // can use this range!    
    button_5 = 85,
    button_6 = 86,
    button_7 = 87,
    button_8 = 88,
 
    //91-95 effect 1-5 depth
    effect_1_depth = 91,
    effect_2_depth = 92,
    effect_3_depth = 93,
    effect_4_depth = 94,
    effect_5_depth = 95,

    //96-101 don't use
    
    //102-119 undefined
    // can use this range!
    slider_1 = 102,
    slider_2 = 103,
    slider_3 = 104,
    slider_4 = 106,
    slider_5 = 107,
    slider_6 = 108,
    slider_7 = 109,
    
    //120-127 channel mode messages --- implement an "all notes off" button press
    all_sound_off = 120,
    all_controllers_off = 121,
    local_keyboard_on_off = 122,
    all_notes_off = 123,
    omni_mode_off = 124,
    omni_mode_on = 125,
    mono_operaton = 126,
    poly_operation = 127
};

//enum of General MIDI drums (pitch 35 - pitch 81)
//modify to full range of midi pitch (0 - 127)?
enum generalMIDIdrums {
    
    /*
    DRUM_0 = 36,        //BASS DRUM
    DRUM_1 = 40,        //ELECTRIC SNARE
    DRUM_2 = 42,        //CLOSED HI-HAT
    DRUM_3 = 49,        //CRASH CYMBAL
    
    DRUM_4 = 36,        //BASS DRUM
    DRUM_5 = 40,        //ELECTRIC SNARE
    DRUM_6 = 42,        //CLOSED HI-HAT
    DRUM_7 = 49,        //CRASH CYMBAL
    */
    
    /*
    DRUM_0 = 36,
    DRUM_1 = 40,
    DRUM_2 = 41,
    DRUM_3 = 43,
    
    DRUM_4 = 42,
    DRUM_5 = 44,
    DRUM_6 = 46,
    DRUM_7 = 51,
    */
    
DRUM_0 = 36,            //C1 Bass Drum 1
DRUM_1 = 38,            //D1 Acoustic Snare
DRUM_2 = 39,            //Eb1 Hand Clap
DRUM_3 = 40,            //E1 Electric Snare

DRUM_4 = 42,            //F#1 Closed Hi Hat
DRUM_5 = 46,            //Bb1 Open Hi-Hat
DRUM_6 = 49,            //C#2 Crash Cymbal 1
DRUM_7 = 54,            //F#2 Tambourine

};

#endif