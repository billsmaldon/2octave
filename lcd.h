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

#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

#include <xc.h>
#define _XTAL_FREQ 20000000

//pins of LCD
#define RS RE0
#define EN RE1
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

//LCD functions
void Lcd_SetBit(char data_bit);
void Lcd_Cmd(char a);
void Lcd_Clear(void);
void Lcd_Set_Cursor(char a, char b);
void Lcd_Start(void);
void Lcd_Print_Char(char data);
void Lcd_Print_String(char *a);

#endif


