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

#include "midi.h"
#include "arpeggio.h"

//USART transmit one byte

// pass 3 bytes to this function at once!
/*
void sendOut (unsigned char a ) {

    TXREG = a;
    while(!TXIF);
    TXIF = 0;
    __delay_us(delay_bytes);

}
*/

void sendOut(unsigned char message1, unsigned char message2, unsigned char message3){

    unsigned char midiMessage[3];//temporary array to store midi messages and shift out
    unsigned char number_of_midi_message_bytes;
    
    midiMessage[0]=message1;
    midiMessage[1]=message2;
    midiMessage[2]=message3;    
    
    // USB works!
    // DIN connector works!
    
    //wrong noteOn() based on controller turned!
    //controlChange() was sending a noteOn()!
    //controllerNumber was being sent as a pitch!!!

    // this code works --->!!! NEED THIS !!!
    if(CONTROL_CHANGE_IS_BEING_SENT == 1) {
        midiMessage[0] = channel | control_change; //this line fixes corrupted midi message (statusByte is wrong)
        midiMessage[1] = GLOBAL_CC_NUMBER; //need these 2 lines too!
        midiMessage[2] = GLOBAL_CC_VALUE;
        CONTROL_CHANGE_IS_BEING_SENT = 0; //added this!
    }

    //program change is a 2 byte message!    
    if(midiMessage[0] == (channel | program_change)){number_of_midi_message_bytes = 2;}
    else{number_of_midi_message_bytes = 3;}

    
    for(unsigned char i=0;i<number_of_midi_message_bytes;i++){ //iterate over 3 bytes
        TXREG = midiMessage[i];
        //while(!TXIF); //try something else:
        while(!TRMT); //this also works!
        TXIF = 0;
        __delay_us(delay_bytes);  //TRY COMMENT THIS OUT!
    }

}

//USB transmit one midi message (3x bytes)
void sendUSB (unsigned char message1, unsigned char message2, unsigned char message3){
   
    unsigned char midiMessage[3];//temporary array to store midi messages and shift out
    
    midiMessage[0]=message1;
    midiMessage[1]=message2;
    midiMessage[2]=message3;
    
    clockPin = 0;
    messageReady = 1; //messageReady HIGH
    __delay_us(50);
    
    for(unsigned char i=0;i<3;i++){ //iterate over 3 bytes
        for(unsigned char ii=0;ii<8;ii++){ //iterate over 8 bits

            //shift out the bits here
            dataPin = !!(midiMessage[i] & (1 << ii)); //LSBFIRST

            __delay_us(50); //added this delay
            
            clockPin = 1; //clock HIGH
            __delay_us(50); //added this delay
            
            clockPin = 0; //clock LOW
            __delay_us(50); //added this delay
        }
    }
    
    messageReady = 0; //messageReady LOW
    __delay_us(50); //added this delay
}


//note off - main channel
void noteOff (unsigned char channel, unsigned char pitch, unsigned char velocity) {

    noteNumber = pitch + semitone + ((octave + 1)* 12);
    statusByte = channel | note_off;

    #ifdef MIDI_V_2_0_BOARD
        //transmit to USB here
        sendUSB(statusByte, noteNumber, 0);
    #endif

    sendOut(statusByte, noteNumber, 0);
}

//note on - main channel
void noteOn (unsigned char channel, unsigned char pitch, unsigned char velocity) {
    
    noteNumber = pitch + semitone + ((octave + 1) * 12);
    statusByte = channel | note_on;

    //velocity 0 = noteOff ---> put this before sendUSB()
    if (velocity == 0) {noteOff(channel, pitch, 0);return;}

    #ifdef MIDI_V_2_0_BOARD
        sendUSB(statusByte, noteNumber, velocity);
    #endif

    if(velocity > 0) {
       sendOut(statusByte, noteNumber, velocity);
       //sendOut(noteNumber);
       //sendOut(velocity);
    }

    note_off_was_sent = 0; //leave this! (clear to 0)
}

//note off - drum channel
void noteOffDrum (unsigned char channel, unsigned char pitch, unsigned char velocity) {
    
    noteNumber = pitch;
    statusByte = channel | note_off;
    
    #ifdef MIDI_V_2_0_BOARD
        sendUSB(statusByte, noteNumber, velocity);
    #endif
    
    sendOut(statusByte, noteNumber, velocity);
    //sendOut(noteNumber);
    //sendOut(velocity);
}

//note on - drum channel
void noteOnDrum (unsigned char channel, unsigned char pitch, unsigned char velocity) {
    
    noteNumber = pitch;
    statusByte = channel | note_on;

    if (velocity == 0) {noteOff(channel, pitch, velocity);return;}
    
    #ifdef MIDI_V_2_0_BOARD
        sendUSB(statusByte, noteNumber, velocity);
    #endif
    
    if(velocity > 0) {
       sendOut(statusByte, noteNumber, velocity);
       //sendOut(noteNumber);
       //sendOut(velocity);
    }
}

//transmit a control change
void controlChange (unsigned char channel, unsigned char controllerNumber, unsigned char value) {

    // *** NEED THIS CODE! ***
    if((note_off_was_sent == 0) && ((TIMER_OVERFLOWS % NOTE_LENGTH_PULSES) == 0)){
        //if next PPQN, call note off
        key_press_release_note_off();
    }

    statusByte = channel | control_change;

    #ifdef MIDI_V_2_0_BOARD
        sendUSB(statusByte, controllerNumber, value);
    #endif
    
    //these fix corrupted midi messages in sendOut()!
    GLOBAL_STATUS_BYTE = statusByte;
    GLOBAL_CC_NUMBER = controllerNumber;
    GLOBAL_CC_VALUE = value;
    
    CONTROL_CHANGE_IS_BEING_SENT = 1;
    sendOut(statusByte, controllerNumber, value);
    //sendOut(controllerNumber);
    //sendOut(value);
    CONTROL_CHANGE_IS_BEING_SENT = 0;
}

//transmit a pitch bend
void pitchBend (unsigned char channel, unsigned char lowByte,  unsigned char highByte) {
    
    //pasted this from controlChange()
    if((note_off_was_sent == 0) && ((TIMER_OVERFLOWS % NOTE_LENGTH_PULSES) == 0)){
        //if next PPQN, call note off
        key_press_release_note_off();
    }

    statusByte = channel | pitch_bend;
    
    #ifdef MIDI_V_2_0_BOARD
        sendUSB(statusByte, lowByte, highByte);
    #endif
    
    sendOut(statusByte, lowByte, highByte);
    //sendOut(lowByte);
    //sendOut(highByte);
}

void programChange (unsigned char channel, unsigned char data1,  unsigned char data2) {

    //pasted this from controlChange()
    //probably not needed, but will prevent stuck noteOn()s if sending a program change while arpeggiator is ON
    if((note_off_was_sent == 0) && ((TIMER_OVERFLOWS % NOTE_LENGTH_PULSES) == 0)){
        //if next PPQN, call note off
        key_press_release_note_off();
    }    

    statusByte = channel | program_change;
    
    #ifdef MIDI_V_2_0_BOARD
        sendUSB(statusByte, data1, data2); // TEST THIS!!! (program change over USB)
    #endif
    
    sendOut(statusByte, data1, data2);
    //sendOut(data1);
    //sendOut(data2); // only 1 byte after statusByte
}