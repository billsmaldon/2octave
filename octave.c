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

#include "octave.h"

//sets octave/semitone
void processOctave(void) {
    
    //octave++
    if(button_state_now == BUTTON_26){
        if ((octave * 12 + semitone) <= 60) { // !!! DONE !!!
            octave++;
            if (octave > 7) {octave = 7;}
            DISPLAY_MODE = DIGITS;
            DIGIT_MODE = BCD;
            number_to_display = octave;
        }
    }
    
    //octave--
    if(button_state_now == BUTTON_25){
        if ((octave * 12 + semitone) >= 12) { // !!! DONE !!!
            octave--;
            if (octave < 0) {octave = 0;}
            DISPLAY_MODE = DIGITS;
            DIGIT_MODE = BCD;
            number_to_display = octave;
        }
    }
    
    //semitone transpose (uses modifier)
    //BUTTON_27 is modifier
    
    //semitone++
    if(button_state_now == (BUTTON_26 | BUTTON_27)){
        
        if ((octave * 12 + semitone) < 72) {  // !!! ++ semitone needs work !!!
            if (TRANSPOSE_MODE == HALF_STEP) {
                semitone++;
                if (semitone > 12) {semitone = 12;}
            }
            if (TRANSPOSE_MODE == CIRCLE_OF_FIFTHS) {
                semitone = (semitone +=7) % 12;
            }
            DISPLAY_MODE = DIGITS;
            DIGIT_MODE = BCD;
            number_to_display = semitone;
        }
    }
    //semitone--
    if(button_state_now == (BUTTON_25 | BUTTON_27)){

        if ((octave * 12 + semitone) > 0 ) {  // !!! -- semitone needs work !!!
        //if ((octave * 12 + semitone) >= 12 ) {
            if (TRANSPOSE_MODE == HALF_STEP) {
                semitone--;
                if (semitone < -12) {semitone = -12;}}
            if (TRANSPOSE_MODE == CIRCLE_OF_FIFTHS) {
                semitone = (semitone -=7) % 12;
            }
            DISPLAY_MODE = DIGITS;
            DIGIT_MODE = BCD;
            number_to_display = semitone;
        }
    }
}