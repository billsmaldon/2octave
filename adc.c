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

#include "adc.h"

//initialize ADC
void ADC_Initialize(void)
{
    CMCON = 0x7;            //turn off PORTA peripherals - comparators OFF
    ADCON0 = 0b00000000;
    ADCON1 = 0b00001110;    //one ADC input (AN0) - connected to 74HC4067 MUX IC
    ADCON2 = 0b10000010;    //ADC result is right justified
                            //A/D Acquisition Time Select bits is 0 TAD
                            //A/D Conversion Clock Select bits is Fosc/32

    ADON = 1;               //ADC ON
}

//reads a 10 bit sample and returns it
unsigned int ADC_Read(unsigned char adc_channel)
{
    //SELECTOR BITS ARE REVERSED ON PCB
    //code to reverse order of bits below:
    
    unsigned char bit_0 = adc_channel & 0x01;
    unsigned char bit_1 = adc_channel & 0x02;
    unsigned char bit_2 = adc_channel & 0x04;
    unsigned char bit_3 = adc_channel & 0x08;
    adc_channel = (bit_0 << 3) | (bit_1 << 1) | (bit_2 >> 1) | (bit_3 >> 3);
    
    adc_channel &= 0x0F;        //bitmask the ADC channel
    ADCON0 &= 0x00000001;       //Clear the Channel Selection Bits
    PORTA = (adc_channel << 1); //Set the channel select bits (on PORTA)
    //PORTA = (adc_channel); //Set the channel select bits (on PORTA)
    __delay_us(20);             //Acquisition time to charge hold capacitor
    GO_nDONE = 1;               //Initializes A/D Conversion
    while(GO_nDONE);            //Wait for A/D Conversion to complete
    return ((ADRESH<<8)+ADRESL);//Returns Result
}
