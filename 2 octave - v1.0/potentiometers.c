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

#include "potentiometers.h"

#define NUM_ANALOG 16

//arduino function used to map potentiometers
long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//gets potentiometer inputs and smooths them with filter algorithm
void readPotentiometers(void){
    
    static __bit FIRST_READING;     //on first potentiometer reading, sets ema_sum[i] to potentiometer_raw[i]
                                    //suppresses transmit of entire bank of continuous controllers on reset
    
    //raw potentiometer input
    for(unsigned char i=0;i<NUM_ANALOG;i++){
        
        potentiometer_raw[i] = ADC_Read(i);     //potentiometer_raw is 10 bits!
        
        //correct reverse polarity on joystick (comment out for now)
        if((i==14 || i==15)){potentiometer_raw[i] = 1023 - potentiometer_raw[i];}
        
        //first reading for potentiometer input smoothing
        if (FIRST_READING == 0) {
            ema_sum[i] = potentiometer_raw[i];
        }
    }

    //filtered potentiometer input
    for(unsigned char i=0;i<NUM_ANALOG;i++){
        ema_sum[i] = (ema_alpha * potentiometer_raw[i]) + ((1 - ema_alpha) * ema_sum[i]);
    }
    
    //potentiometer_filtered_now[i] = ema_sum[i]; //update the variable

    //do the hysteresis and bit-shifting
    for(unsigned char i = 0; i<NUM_ANALOG; i++){
        
        
        //switches from coarse to fine on mismatch *works*
        //switch from fine back to coarse after a short delay *works*
        //make the code stick with most current control being turned *next*
        
        //"last control turned" = "next control turned"
        //to eliminate fluctuations in controllers that are not currently being turned
        
        static unsigned long long int count;
        count++;
        //static unsigned char iterator_focus;
          
        if (FIRST_READING == 0) {potentiometer_filtered_last[i] = ema_sum[i];}
        
        if (((int)(ema_sum[i] - potentiometer_filtered_last[i]) >= HYST_VAL) || ((int)(potentiometer_filtered_last[i] - ema_sum[i]) >= HYST_VAL)) { //hysteresis

            if((i==iterator_focus) || (iterator_focus==FREE)) {count = 0;} //count is resetting when any "i" is turned, not just "iterator_focus"
            HYST_VAL = HYST_VAL_FINE_RESOLUTION;
            if(iterator_focus == FREE) {iterator_focus = i;}
            potentiometer_filtered_now[i] = ema_sum[i]; //update the variable
            
            //bit shifting (7 bit)
            if(inputPotsArray[i].controller_resolution == LO_RES) {
                potentiometer_filtered_now[i] = map(potentiometer_filtered_now[i], 0, 0x3F50, 0, 0x3FFF);
                potentiometer_filtered_now[i] = potentiometer_filtered_now[i] >> 3;
                if(potentiometer_filtered_now[i] < 0){potentiometer_filtered_now[i] = 0;}
                if(potentiometer_filtered_now[i] > 127){potentiometer_filtered_now[i] = 127;}
            }
            
            //bit shifting (14 bit)
            if(inputPotsArray[i].controller_resolution == HI_RES) {
                potentiometer_filtered_now[i] = potentiometer_filtered_now[i] << 4;
                potentiometer_filtered_now[i] = map(potentiometer_filtered_now[i], 0x50, 0x3F00, 0, 0x3FFF);
                //limit to 2 byte MIDI range (0x0000 - 0x3FFF)
                if(potentiometer_filtered_now[i] < 0){potentiometer_filtered_now[i] = 0;}
                if(potentiometer_filtered_now[i] > 0x3FFF){potentiometer_filtered_now[i] = 0x3FFF;}
            }
            
            // !!! LEFT OFF HERE !!!
            // focus on controller that is iterator "i" (mismatch)
            // ignore other controller numbers if mainly iterator "i" is the only potentiometer that is varying
            
            //this sends any "i" to "iterator_focus" ---> fix
            if(i==iterator_focus) {processPotentiometers(iterator_focus);} //if there is a mismatch, pass the iterator
            potentiometer_filtered_last[i] = ema_sum[i]; //update the variable
            
        }
        
        //this code switches FINE/COARSE resolution after a time delay
        if (count > number_of_repeats) {
            //DISPLAY_MODE = DIGITS;  //display set to "DIGITS"
            //DIGIT_MODE = BCD;       //number base set to "BCD"
            //number_to_display = 999; // test print (comment out)
            HYST_VAL = HYST_VAL_COARSE_RESOLUTION;
            iterator_focus = FREE;
        }
    }
    
    FIRST_READING = 1;
}

//transmits midi control changes (send control change)
void processPotentiometers(unsigned char i){
    
    number_to_display = potentiometer_filtered_now[i];  //display most recently turned knob
    
    //LO RES CONTROLLER HERE
    if (inputPotsArray[i].controller_resolution == LO_RES){
        
        DISPLAY_MODE = DIGITS;  //display set to "DIGITS"
        DIGIT_MODE = BCD;       //number base set to "BCD"

        //regular control change
        if(inputPotsArray[i].controller_number >= 0) {
            controlChange(channel, inputPotsArray[i].controller_number, potentiometer_filtered_now[i]);
        }
        
        //is a controller number with a display string (is VELOCITY)
        if(inputPotsArray[i].controller_number == -1) {
            velocity = potentiometer_filtered_now[i];
        }
        //is a controller number with a display string (is PITCHBEND)
        if(inputPotsArray[i].controller_number == -2) {
            pitchBend(channel, 0x00, potentiometer_filtered_now[i]);  //select the pitch bender
        }
        
        //is a controller number with a display string (is MOD.WHEEL)
        if(inputPotsArray[i].controller_number == -3) {
            controlChange(channel, modulation_wheel_MSB, potentiometer_filtered_now[i]);  //select the modulation wheel
        }          
    }

    //HI RES CONTROLLER HERE
    if (inputPotsArray[i].controller_resolution == HI_RES){
        
        DISPLAY_MODE = DIGITS;  //display set to "DIGITS"
        DIGIT_MODE = HEX2;      //display set to "HEX2" (splits hex value into "highByte", "lowByte")
                    
        //split potentiometer_filtered_now into 2 bytes:
        unsigned char lowByte =  (potentiometer_filtered_now[i]) &  0x7F;
        unsigned char highByte = (potentiometer_filtered_now[i] >> 7) & 0x7F;
        
        //regular control change
        if(inputPotsArray[i].controller_number_two_byte >= 0) {
            controlChange(channel, inputPotsArray[i].controller_number_two_byte, highByte);
            controlChange(channel, inputPotsArray[i].controller_number_two_byte + 32, lowByte);
        }
        //is a controller number with a display string (is VELOCITY)
        if(inputPotsArray[i].controller_number_two_byte == -1) {
            velocity = highByte;
        }
        //is a controller number with a display string (is PITCHBEND)
        if(inputPotsArray[i].controller_number_two_byte == -2) {
            pitchBend(channel, lowByte, highByte);  //select the pitch bender
        }
        //is a controller number with a display string (is MOD.WHEEL)
        if(inputPotsArray[i].controller_number_two_byte == -3) {
            controlChange(channel, modulation_wheel_MSB, highByte);  //select the modulation wheel
            controlChange(channel, modulation_wheel_MSB + 32, lowByte);
        }  
    }
}

