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
void sendOut (unsigned char a ) {

    TXREG = a;
    while(!TXIF);
    TXIF = 0;
    __delay_us(delay_bytes);

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
        sendUSB(statusByte, noteNumber, velocity);
    #endif

    sendOut(statusByte);
    sendOut(noteNumber);
    sendOut(velocity);

}

//note on - main channel
void noteOn (unsigned char channel, unsigned char pitch, unsigned char velocity) {
    
    noteNumber = pitch + semitone + ((octave + 1) * 12);
    statusByte = channel | note_on;

    //velocity 0 = noteOff ---> put this before sendUSB()
    if (velocity == 0) {noteOff(channel, pitch, velocity);return;}
    
    #ifdef MIDI_V_2_0_BOARD
        sendUSB(statusByte, noteNumber, velocity);
    #endif

    if(velocity > 0) {
       sendOut(statusByte);
       sendOut(noteNumber);
       sendOut(velocity);
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
    
    sendOut(statusByte);
    sendOut(noteNumber);
    sendOut(velocity);
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
       sendOut(statusByte);
       sendOut(noteNumber);
       sendOut(velocity);
    }
}

//transmit a control change
void controlChange (unsigned char channel, unsigned char controllerNumber, unsigned char value) {

    statusByte = channel | control_change;
    
    #ifdef MIDI_V_2_0_BOARD
        sendUSB(statusByte, controllerNumber, value);
    #endif
    
    sendOut(statusByte);
    sendOut(controllerNumber);
    sendOut(value);
}

//transmit a pitch bend
void pitchBend (unsigned char channel, unsigned char lowByte,  unsigned char highByte) {

    statusByte = channel | pitch_bend;
    
    #ifdef MIDI_V_2_0_BOARD
        sendUSB(statusByte, lowByte, highByte);
    #endif
    
    sendOut(statusByte);
    sendOut(lowByte);
    sendOut(highByte);
}

void programChange (unsigned char channel, unsigned char data1,  unsigned char data2) {

    statusByte = channel | program_change;
    
    #ifdef MIDI_V_2_0_BOARD
        sendUSB(statusByte, data1, data2); // TEST THIS!!! (program change over USB)
    #endif
    
    sendOut(statusByte);
    sendOut(data1);
    //sendOut(data2); // only 1 byte after statusByte
}