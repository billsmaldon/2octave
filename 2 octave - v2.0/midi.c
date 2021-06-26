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

//USART transmit one byte
void sendOut (unsigned char a ) {

    TXREG = a;
    while(!TXIF);
    TXIF = 0;

}

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
    
    sendUSB(statusByte, noteNumber, velocity);
    
    sendOut(statusByte);
    __delay_ms(2);
    //__delay_us(320);
    sendOut(noteNumber);
    __delay_ms(2);
    //__delay_us(320);
    sendOut(velocity);
    __delay_ms(2);
    //__delay_us(320);
    
    //transmit to USB here
    
}

//note on - main channel
void noteOn (unsigned char channel, unsigned char pitch, unsigned char velocity) {
    
    noteNumber = pitch + semitone + ((octave + 1) * 12);
    statusByte = channel | note_on;
    
    sendUSB(statusByte, noteNumber, velocity);
    
    //velocity 0 = noteOff
    if (velocity == 0) {noteOff(channel, pitch, velocity);return;}
    
    else {
       sendOut(statusByte);
        __delay_ms(2);
        //__delay_us(320);
       sendOut(noteNumber);
        __delay_ms(2);
       //__delay_us(320);
       sendOut(velocity);
        __delay_ms(2);
       //__delay_us(320);
    }
}

//note off - drum channel
void noteOffDrum (unsigned char channel, unsigned char pitch, unsigned char velocity) {
    
    noteNumber = pitch;
    statusByte = channel | note_off;
    
    sendUSB(statusByte, noteNumber, velocity);
    
    sendOut(statusByte);
    __delay_ms(2);
    //__delay_us(320);
    sendOut(noteNumber);
    __delay_ms(2);
    //__delay_us(320);
    sendOut(velocity);
    __delay_ms(2);
    //__delay_us(320);
}

//note on - drum channel
void noteOnDrum (unsigned char channel, unsigned char pitch, unsigned char velocity) {
    
    noteNumber = pitch;
    statusByte = channel | note_on;
    
    sendUSB(statusByte, noteNumber, velocity);

    if (velocity == 0) {noteOff(channel, pitch, velocity);return;}
    
    else {
       sendOut(statusByte);
        __delay_ms(2);
        //__delay_us(320);
       sendOut(noteNumber);
        __delay_ms(2);
       //__delay_us(320);
       sendOut(velocity);
        __delay_ms(2);
       //__delay_us(320);
    }
}

//transmit a control change
void controlChange (unsigned char channel, unsigned char controllerNumber, unsigned char value) {

    statusByte = channel | control_change;
    
    sendUSB(statusByte, controllerNumber, value);
    
    sendOut(statusByte);
    __delay_ms(2);
    //__delay_us(320);
    sendOut(controllerNumber);
    __delay_ms(2);
    //__delay_us(320);
    sendOut(value);
    __delay_ms(2);
    //__delay_us(320);
}

//transmit a pitch bend
void pitchBend (unsigned char channel, unsigned char lowByte,  unsigned char highByte) {

    statusByte = channel | pitch_bend;
    
    sendUSB(statusByte, lowByte, highByte);
    
    sendOut(statusByte);
    __delay_ms(2);
    //__delay_us(320);
    sendOut(lowByte);
    __delay_ms(2);
    //__delay_us(320);
    sendOut(highByte);
    __delay_ms(2);
    //__delay_us(320);
}

void programChange (unsigned char channel, unsigned char data1,  unsigned char data2) {

    statusByte = channel | program_change;
    
    sendUSB(statusByte, data1, data2);
    
    sendOut(statusByte);
    __delay_ms(2);
    //__delay_us(320);
    sendOut(data1);
    __delay_ms(2);
    //__delay_us(320);
    sendOut(data2);
    __delay_ms(2);
    //__delay_us(320);    
    
}