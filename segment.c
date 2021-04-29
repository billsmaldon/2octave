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

#include "segment.h"

//function refreshes 7 segment display exactly once
//either set to "DIGITS" or "STRING
void display(void) {
    if (DISPLAY_MODE == DIGITS) {displayDigits();}
    if (DISPLAY_MODE == STRING) {displayString();}
}

//display numbers on 7-seg
//set to "BCD" to display a signed integer number (999 to -999)
//set to "HEX" to display a number in hexadecimal
//set to "HEX2" to display hexadecimal as "highByte", "lowByte" (for two byte MIDI controls)
void displayDigits(void){
    
    unsigned char digit[4];
    
    static __bit isNegative = 0;
    signed int number_to_display_temp = 0;
    
    //handles signed integers
    if (DIGIT_MODE == BCD) {
        
        if(number_to_display < 0) {
            isNegative = 1;
            number_to_display_temp = (0 - number_to_display);
        }
        else {
            isNegative = 0;
            number_to_display_temp = number_to_display;
        }
        
    }
 
    if(DIGIT_MODE == BCD) { //BCD
        //digit[0] = (number_to_display_temp / 1000) % 10;  //thou 10^3
        digit[1] = (number_to_display_temp / 100) % 10;     //hund 10^2
        digit[2] = (number_to_display_temp / 10) % 10;      //tens 10^1
        digit[3] =  number_to_display_temp % 10;            //ones 10^0
    }

    if(DIGIT_MODE == HEX) { //HEX
        digit[0] = (number_to_display >> 12) % 16;  //16^3
        digit[1] = (number_to_display >> 8) % 16;   //16^2
        digit[2] = (number_to_display >> 4) % 16;   //16^1
        digit[3] =  number_to_display % 16;         //16^0
    }
    
    if(DIGIT_MODE == HEX2) { //HEX
            
        unsigned char lowByte =  number_to_display &  0x7F;
        unsigned char highByte = (number_to_display >> 7) & 0x7F;
            
        digit[0] =  (highByte >> 4) % 0x8;  //16^3
        digit[1] =  highByte % 16;          //16^2
        digit[2] =  (lowByte >> 4) % 0x8;   //16^1
        digit[3] =  lowByte % 16;           //16^0
  
    }

    if (DIGIT_MODE == BCD) {
        
        //if number_to_display < 0, light segment 'G' (minus)
        if(isNegative) {
            PORTD = 0b01000000; RC0 = 1;        
            __delay_ms(digit_delay); RC0 = 0;
        }
    
        //blank leading zeros --- unfinished
        /*
        if(!isNegative){
            PORTD = seg_bcd_hex[digit[0]]; RC0 = 1;     //change to [0]
            __delay_ms(digit_delay); RC0 = 0;
        }
        */
        
        PORTD = seg_bcd_hex[digit[1]]; RC1 = 1;  //change to [1]
        __delay_ms(digit_delay); RC1 = 0;
        PORTD = seg_bcd_hex[digit[2]]; RC2 = 1;  //change to [2]
        __delay_ms(digit_delay); RC2 = 0;
        PORTD = seg_bcd_hex[digit[3]]; RC3 = 1;  //change to [3]
        __delay_ms(digit_delay); RC3 = 0;
    }
    
    if (DIGIT_MODE == HEX || DIGIT_MODE == HEX2) {
        PORTD = seg_bcd_hex[digit[0]]; RC0 = 1;     //change to [0]
        __delay_ms(digit_delay); RC0 = 0;
        PORTD = seg_bcd_hex[digit[1]]; RC1 = 1;     //change to [1]
        __delay_ms(digit_delay); RC1 = 0;
        PORTD = seg_bcd_hex[digit[2]]; RC2 = 1;     //change to [2]
        __delay_ms(digit_delay); RC2 = 0;
        PORTD = seg_bcd_hex[digit[3]]; RC3 = 1;     //change to [3]
        __delay_ms(digit_delay); RC3 = 0;
    
    }
}

//display letters on 7-seg
//function to display an ASCII string (4 chars)
void displayString(void){
    
    unsigned char letter[4];
    
    //out of range check and starts ascii table at '0'
    for(unsigned char i=0;i<4;i++) {
        if(string_to_display[i] > (unsigned char) 'z') {letter[i] = 'z';}
        else letter[i] = string_to_display[i] - '0';
    }
    
    //for common anode display, bitwise NOT (~) digit to display
    PORTD = seg_ascii[letter[0]]; RC0 = 1;
    __delay_ms(digit_delay); RC0 = 0;
    PORTD = seg_ascii[letter[1]]; RC1 = 1;
    __delay_ms(digit_delay); RC1 = 0;
    PORTD = seg_ascii[letter[2]]; RC2 = 1;
    __delay_ms(digit_delay); RC2 = 0;
    PORTD = seg_ascii[letter[3]]; RC3 = 1;
    __delay_ms(digit_delay); RC3 = 0;

}

