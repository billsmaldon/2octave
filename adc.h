/* This file is part of Foobar.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <https://www.gnu.org/licenses/>.

*/

#ifndef ADC_H_INCLUDED
#define ADC_H_INCLUDED

#include <xc.h>
#define _XTAL_FREQ 20000000

//initialize ADC
void ADC_Initialize(void);
//reads a 10 bit sample and returns it
unsigned int ADC_Read(unsigned char adc_channel);

#endif