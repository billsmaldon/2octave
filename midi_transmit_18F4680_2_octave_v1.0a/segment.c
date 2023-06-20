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

//either set to "DIGITS" or "STRING
void display(void) {
    if (DISPLAY_MODE == DIGITS) {displayDigits();}
    if (DISPLAY_MODE == STRING) {displayString();}
}

//display numbers on 7-seg
//set to "BCD" to display a signed integer number (9999 to -999)
//set to "HEX" to display a number in hexadecimal
//set to "HEX2" to display hexadecimal as "highByte", "lowByte" (for two byte MIDI controls)

void displayTest(void){
    
    //display "tESt" for 500 mS
    //display screen test for 1.0 S
    //return to blank display
    
    DISPLAY_MODE = STRING;
    strcpy(string_to_display,"tESt");

    __delay_ms(500);
    
    DISPLAY_MODE = DIGITS;
    DIGIT_MODE = BCD;
    number_to_display = 8888;
    light_decimal_points = 1;
    __delay_ms(1000);
    light_decimal_points = 0;
    
    DISPLAY_MODE = STRING;
    strcpy(string_to_display,"    ");    
    
}

void displayDigits(void){
    
    //calculate segments only ONCE when a mismatch of *now* and *last*
    //digit counter 1-4, increments ONE every time displayDigitsISR called in ISR
    //no need for delay() function!

    static unsigned char digit[4];
    static unsigned char digit_counter;
    static signed int number_to_display_last;
    static signed int number_to_display_temp;
 
    //these blocks of code CALCULATE the SEGMENTS 
    if(number_to_display != number_to_display_last){
        //calculate segments
        if(DIGIT_MODE == BCD) { //BCD
        
            if(number_to_display >= 0){number_to_display_temp = number_to_display;}
            if(number_to_display < 0){number_to_display_temp = 0 - number_to_display;}

            digit[0] = (number_to_display_temp / 1000) % 10;    //thou 10^3
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
    
        //end mismatch of now and last
        number_to_display_last = number_to_display;
    }

    //these blocks of code turn on the SEGMENTS
    if (DIGIT_MODE == BCD || DIGIT_MODE == HEX || DIGIT_MODE == HEX2) {
        
        //blank leading zeros --- DONE!
        //floating minus sign --- NEXT
         
            if(digit_counter == 0){
                RC3 = 0;
                
                //this block of code prints the "minus" sign to the leftmost digit
                if(DIGIT_MODE == BCD && number_to_display < 0){
                    //commented this out!
                    //PORTD = 0x40; RC0 = 1;
                    if(digit[1] > 0){PORTD = 0x40; RC0 = 1;} //was !=0
                    if(light_decimal_points == 1){PORTD |= 0x80;}
                }
            
                else {
                    PORTD = seg_bcd_hex[digit[0]];
                    if(light_decimal_points == 1){PORTD |= 0x80;}
                    if(digit[0] == 0){RC0 = 0;}
                    else{RC0 = 1;}
                }
            }
            if(digit_counter == 1){
                RC0 = 0;
                PORTD = seg_bcd_hex[digit[1]];
                if(light_decimal_points == 1){PORTD |= 0x80;}
                if(digit[0] == 0 && digit[1] == 0){RC1 = 0;}
                else{RC1 = 1;}
                //added these 3 lines!
                if(DIGIT_MODE == BCD && number_to_display < 0){
                    //if(digit[2] > 0){PORTD = 0x40; RC1 = 1;} //commented this out
                    if(digit[2] > 0 && digit[1] == 0){PORTD = 0x40; RC1 = 1;} //this line!
                }
            }
            if(digit_counter == 2){
                RC1 = 0;
                PORTD = seg_bcd_hex[digit[2]];
                if(light_decimal_points == 1){PORTD |= 0x80;}
                if(digit[0] == 0 && digit[1] == 0 && digit[2] == 0){RC2 = 0;}
                else{RC2 = 1;}
                //added these 3 lines!
                if(DIGIT_MODE == BCD && number_to_display < 0){
                    if(digit[3] > 0 && digit[2] == 0){PORTD = 0x40; RC2 = 1;} //this line!
                }                
            }
            if(digit_counter == 3){
                RC2 = 0;
                PORTD = seg_bcd_hex[digit[3]];
                if(light_decimal_points == 1){PORTD |= 0x80;}
                RC3 = 1;
            }
        }
    
    //light next display
    digit_counter++;
    if(digit_counter > 3){digit_counter = 0;}
}

//display letters on 7-seg
//function to display an ASCII string (4 chars)
void displayString(void){
    
    static unsigned char letter[4];
    static unsigned char letter_counter;
    
    //out of range check and starts ascii table at '0'
    for(unsigned char i=0;i<4;i++) {
        if(string_to_display[i] > (unsigned char) 'z') {letter[i] = 'z';}
        else letter[i] = string_to_display[i] - '0';
    }
    
    if(letter_counter == 0){
        RC3 = 0;
        PORTD = seg_ascii[letter[0]];
        RC0 = 1;
    }
    if(letter_counter == 1){
        RC0 = 0;
        PORTD = seg_ascii[letter[1]];
        RC1 = 1;
    }
    if(letter_counter == 2){
        RC1 = 0;
        PORTD = seg_ascii[letter[2]];
        RC2 = 1;
    }
    if(letter_counter == 3){
        RC2 = 0;
        PORTD = seg_ascii[letter[3]];
        RC3 = 1;
    }    

    //light next display
    letter_counter++;
    if(letter_counter > 3){letter_counter = 0;}  
}