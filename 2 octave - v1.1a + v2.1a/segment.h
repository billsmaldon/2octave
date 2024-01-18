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

#ifndef SEGMENT_H_INCLUDED
#define SEGMENT_H_INCLUDED

#include <xc.h>
#include <string.h>

#define _XTAL_FREQ 20000000

//function prototypes
void display(void);         //function refreshes 7 segment display at 100 Hz (in ISR)
                            //either set to "DIGITS" or "STRING"
void displayTest(void);     //test 7 segment display
void displayString(void);   //function to display an ASCII string (4 chars)
void displayDigits(void);   //function to display a signed int number (9999 to -999)

void menu(void);

//bits to select display type
//DISPLAY_MODE
#define DIGITS 0 //display a number
#define STRING 1 //display an ascii string
unsigned char DISPLAY_MODE;

__bit light_decimal_points;

//DIGIT_MODE
#define BCD  0    //display number as decimal
#define HEX  1    //display number as hexadecimal '3FFF'
#define HEX2 2    //display hexadecimal number as '7F7F'
unsigned char DIGIT_MODE;

//initialize display number/string variables
signed int number_to_display = -128; //integer to display
unsigned char string_to_display[5] = {'t','E','S','t','\0'}; //character string to display (in ascii)

//7 segment display codes (BCD/HEX):
//Array for displaying hexadecimal numbers from 0 to F
const unsigned char seg_bcd_hex[]={0x3F, //Hex value to display the number 0
                    0x06, //Hex value to display the number 1
                    0x5B, //Hex value to display the number 2
                    0x4F, //Hex value to display the number 3
                    0x66, //Hex value to display the number 4
                    0x6D, //Hex value to display the number 5
                    0x7D, //Hex value to display the number 6
                    0x07, //Hex value to display the number 7
                    0x7F, //Hex value to display the number 8
                    0x6F, //Hex value to display the number 9
		            0x77, //A
                    0x7C, //b
                    0x39, //C
                    0x5E, //d
                    0x79, //E
                    0x71  //F
                   };

//7 segment display codes (ascii):
const unsigned char seg_ascii[75]= {
/*  0     1     2     3     4     5     6     7     8     9     :     ;     */
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x00, 0x00, 
/*  <     =     >     ?     @     A     B     C     D     E     F     G     */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x00, 0x39, 0x00, 0x79, 0x71, 0x3D, 
/*  H     I     J     K     L     M     N     O     P     Q     R     S     */
    0x76, 0x30, 0x1E, 0x00, 0x38, 0x00, 0x00, 0x3F, 0x73, 0x00, 0x00, 0x6D, 
/*  T     U     V     W     X     Y     Z     [     \     ]     ^     _     */
    0x00, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
/*  `     a     b     c     d     e     f     g     h     i     j     k     */
    0x00, 0x5F, 0x7C, 0x58, 0x5E, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00, 
/*  l     m     n     o     p     q     r     s     t     u     v     w     */
    0x00, 0x00, 0x54, 0x5C, 0x00, 0x67, 0x50, 0x00, 0x78, 0x1C, 0x00, 0x00, 
/*  x     y     z     */
    0x00, 0x6E, 0x00
};

#endif