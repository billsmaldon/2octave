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

#include "keyboard.h"

//select keyboard mode
void processKeyboard(void) {
    //CHROMATIC SCALE, TRIADS, SEVENTH CHORDS    
    if ((KEYBOARD_MODE == CHROMATIC) | KEYBOARD_MODE == TRIAD | KEYBOARD_MODE == SEVENTH) {keyboard_all_note();} //play the keyboard
    //MAJOR SCALE, MINOR SCALE, MODES, DIATONIC TRIADS, DIATONIC 7TH CHORDS
    if ((KEYBOARD_MODE == MAJOR) | (KEYBOARD_MODE == MINOR) | (KEYBOARD_MODE == MODES) | (KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR)| (KEYBOARD_MODE == DIATONIC_TRIAD_MINOR)| (KEYBOARD_MODE == DIATONIC_7TH_MAJOR)| (KEYBOARD_MODE == DIATONIC_7TH_MINOR)) {keyboard_eight_note();}
}

//entire keyboard
void keyboard_all_note(void) {
    
    unsigned char pitch;        //is a pitch
    
    unsigned char *triad_p;     //points to a triad
    
    //selects a triad type
    switch (which_triad) {
        case major:
            triad_p = major_triad;
            break;
        case minor:
            triad_p = minor_triad;
            break;
        case augmented:
            triad_p = augmented_triad;
            break;
        case diminished:
            triad_p = diminished_triad;
            break;
        default:
            break;
    }
    
    unsigned char *seventh_p;   //points to a seventh chord
    
    //selects a seventh chord type
    switch (which_seventh) {
       case dominant7:
            seventh_p = dominant_7th;
            break;
        case major7:
            seventh_p = major_7th;
            break;
        case minor7:
            seventh_p = minor_7th;
            break;
        case half_diminished7:
            seventh_p = half_diminished_7th;
            break;
        case diminished7:
            seventh_p = diminished_7th;
            break;
        default:
            break;
    }
    
    // *** NOTE ON *** POLYPHONIC
    if((button_state_now & BUTTON_0) && !keyboard.SW1){
        pitch = C;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0],velocity);
            noteOn(channel,triad_p[1],velocity);
            noteOn(channel,triad_p[2],velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0],velocity);
            noteOn(channel,seventh_p[1],velocity);
            noteOn(channel,seventh_p[2],velocity);
            noteOn(channel,seventh_p[3],velocity);
        }
        keyboard.SW1 = 1;
    }
    if((button_state_now & BUTTON_1) && !keyboard.SW2) {
        pitch = Cs;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }    
        keyboard.SW2 = 1;
    }
    if((button_state_now & BUTTON_2) && !keyboard.SW3) {
        pitch = D;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
       keyboard.SW3 = 1;
    }
    if((button_state_now & BUTTON_3) && !keyboard.SW4) {
        pitch = Ds;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW4 = 1;
    }
    if((button_state_now & BUTTON_4) && !keyboard.SW5) {
        pitch = E;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW5 = 1;
    }
    if((button_state_now & BUTTON_5) && !keyboard.SW6) {
        pitch = F;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW6 = 1;
    }
    if((button_state_now & BUTTON_6) && !keyboard.SW7) {
        pitch = Fs;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW7 = 1;
    }
    if((button_state_now & BUTTON_7) && !keyboard.SW8) {
        pitch = G;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW8 = 1;
    }
    if((button_state_now & BUTTON_8) && !keyboard.SW9) {
        pitch = Gs;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW9 = 1;
    }
    if((button_state_now & BUTTON_9) && !keyboard.SW10) {
        pitch = A;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW10 = 1;
    }
    if((button_state_now & BUTTON_10) && !keyboard.SW11) {
        pitch = As;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW11 = 1;
    }
    if((button_state_now & BUTTON_11) && !keyboard.SW12) {
        pitch = B;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW12 = 1;
    }
    if((button_state_now & BUTTON_12) && !keyboard.SW13) {
        pitch = C2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW13 = 1;
    }
    
    //!!! PASTE 2ND OCTAVE HERE (NOTE ON) !!!
    
    if((button_state_now & BUTTON_13) && !keyboard.SW14){
        pitch = C2s;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0],velocity);
            noteOn(channel,triad_p[1],velocity);
            noteOn(channel,triad_p[2],velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0],velocity);
            noteOn(channel,seventh_p[1],velocity);
            noteOn(channel,seventh_p[2],velocity);
            noteOn(channel,seventh_p[3],velocity);
        }
        keyboard.SW14 = 1;
    }
    if((button_state_now & BUTTON_14) && !keyboard.SW15) {
        pitch = D2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }    
        keyboard.SW15 = 1;
    }
    if((button_state_now & BUTTON_15) && !keyboard.SW16) {
        pitch = D2s;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
       keyboard.SW16 = 1;
    }
    if((button_state_now & BUTTON_16) && !keyboard.SW17) {
        pitch = E2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW17 = 1;
    }
    if((button_state_now & BUTTON_17) && !keyboard.SW18) {
        pitch = F2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW18 = 1;
    }
    if((button_state_now & BUTTON_18) && !keyboard.SW19) {
        pitch = F2s;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW19 = 1;
    }
    if((button_state_now & BUTTON_19) && !keyboard.SW20) {
        pitch = G2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW20 = 1;
    }
    if((button_state_now & BUTTON_20) && !keyboard.SW21) {
        pitch = G2s;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW21 = 1;
    }
    if((button_state_now & BUTTON_21) && !keyboard.SW22) {
        pitch = A2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW22 = 1;
    }
    if((button_state_now & BUTTON_22) && !keyboard.SW23) {
        pitch = A2s;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW23 = 1;
    }
    if((button_state_now & BUTTON_23) && !keyboard.SW24) {
        pitch = B2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW24 = 1;
    }
    if((button_state_now & BUTTON_24) && !keyboard.SW25) {
        pitch = C3;
        if(KEYBOARD_MODE == CHROMATIC) {noteOn(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOn(channel,triad_p[0] + pitch,velocity);
            noteOn(channel,triad_p[1] + pitch,velocity);
            noteOn(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOn(channel,seventh_p[0] + pitch,velocity);
            noteOn(channel,seventh_p[1] + pitch,velocity);
            noteOn(channel,seventh_p[2] + pitch,velocity);
            noteOn(channel,seventh_p[3] + pitch,velocity);
        }            
        keyboard.SW25 = 1;
    }
    
    // !!! END OF PASTE !!!
 
    // *** NOTE OFF *** POLYPHONIC
    if(((button_state_last & BUTTON_0)) && ((button_state_now & BUTTON_0) == 0) && keyboard.SW1) {
        pitch = C;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0],velocity);
            noteOff(channel,triad_p[1],velocity);
            noteOff(channel,triad_p[2],velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                  
        keyboard.SW1 = 0;
    }
    if(((button_state_last & BUTTON_1)) && ((button_state_now & BUTTON_1) == 0) && keyboard.SW2) {
        pitch = Cs;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW2 = 0;
    }
    if(((button_state_last & BUTTON_2)) && ((button_state_now & BUTTON_2) == 0) && keyboard.SW3) {
        pitch = D;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW3 = 0;
    }
    if(((button_state_last & BUTTON_3)) && ((button_state_now & BUTTON_3) == 0) && keyboard.SW4) {
        pitch = Ds;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW4 = 0;
    }
    if(((button_state_last & BUTTON_4)) && ((button_state_now & BUTTON_4) == 0) && keyboard.SW5) {
        pitch = E;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW5 = 0;
    }
    if(((button_state_last & BUTTON_5)) && ((button_state_now & BUTTON_5) == 0) && keyboard.SW6) {
        pitch = F;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW6 = 0;
    }
    if(((button_state_last & BUTTON_6)) && ((button_state_now & BUTTON_6) == 0) && keyboard.SW7) {
        pitch = Fs;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW7 = 0;
    }
    if(((button_state_last & BUTTON_7)) && ((button_state_now & BUTTON_7) == 0) && keyboard.SW8) {
        pitch = G;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW8 = 0;
    }
    if(((button_state_last & BUTTON_8)) && ((button_state_now & BUTTON_8) == 0) && keyboard.SW9) {
        pitch = Gs;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW9 = 0;
    }
    if(((button_state_last & BUTTON_9)) && ((button_state_now & BUTTON_9) == 0) && keyboard.SW10) {
        pitch = A;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW10 = 0;
    }
    if(((button_state_last & BUTTON_10)) && ((button_state_now & BUTTON_10) == 0) && keyboard.SW11) {
        pitch = As;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW11 = 0;
    }
    if(((button_state_last & BUTTON_11)) && ((button_state_now & BUTTON_11) == 0) && keyboard.SW12) {
        pitch = B;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW12 = 0;
    }
    if(((button_state_last & BUTTON_12)) && ((button_state_now & BUTTON_12) == 0) && keyboard.SW13) {
        pitch = C2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW13 = 0;
    }
    
    //!!! PASTE 2ND OCTAVE HERE (NOTE OFF) !!!
    
    if(((button_state_last & BUTTON_13)) && ((button_state_now & BUTTON_13) == 0) && keyboard.SW14) {
        pitch = C2s;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0],velocity);
            noteOff(channel,triad_p[1],velocity);
            noteOff(channel,triad_p[2],velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                  
        keyboard.SW14 = 0;
    }
    if(((button_state_last & BUTTON_14)) && ((button_state_now & BUTTON_14) == 0) && keyboard.SW15) {
        pitch = D2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW15 = 0;
    }
    if(((button_state_last & BUTTON_15)) && ((button_state_now & BUTTON_15) == 0) && keyboard.SW16) {
        pitch = D2s;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW16 = 0;
    }
    if(((button_state_last & BUTTON_16)) && ((button_state_now & BUTTON_16) == 0) && keyboard.SW17) {
        pitch = E2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW17 = 0;
    }
    if(((button_state_last & BUTTON_17)) && ((button_state_now & BUTTON_17) == 0) && keyboard.SW18) {
        pitch = F2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW18 = 0;
    }
    if(((button_state_last & BUTTON_18)) && ((button_state_now & BUTTON_18) == 0) && keyboard.SW19) {
        pitch = F2s;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW19 = 0;
    }
    if(((button_state_last & BUTTON_19)) && ((button_state_now & BUTTON_19) == 0) && keyboard.SW20) {
        pitch = G2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW20 = 0;
    }
    if(((button_state_last & BUTTON_20)) && ((button_state_now & BUTTON_20) == 0) && keyboard.SW21) {
        pitch = G2s;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW21 = 0;
    }
    if(((button_state_last & BUTTON_21)) && ((button_state_now & BUTTON_21) == 0) && keyboard.SW22) {
        pitch = A2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW22 = 0;
    }
    if(((button_state_last & BUTTON_22)) && ((button_state_now & BUTTON_22) == 0) && keyboard.SW23) {
        pitch = A2s;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW23 = 0;
    }
    if(((button_state_last & BUTTON_23)) && ((button_state_now & BUTTON_23) == 0) && keyboard.SW24) {
        pitch = B2;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW24 = 0;
    }
    if(((button_state_last & BUTTON_24)) && ((button_state_now & BUTTON_24) == 0) && keyboard.SW25) {
        pitch = C3;
        if(KEYBOARD_MODE == CHROMATIC) {noteOff(channel,pitch,velocity);}
        if(KEYBOARD_MODE == TRIAD) {
            noteOff(channel,triad_p[0] + pitch,velocity);
            noteOff(channel,triad_p[1] + pitch,velocity);
            noteOff(channel,triad_p[2] + pitch,velocity);
        }
        if(KEYBOARD_MODE == SEVENTH) {
            noteOff(channel,seventh_p[0] + pitch,velocity);
            noteOff(channel,seventh_p[1] + pitch,velocity);
            noteOff(channel,seventh_p[2] + pitch,velocity);
            noteOff(channel,seventh_p[3] + pitch,velocity);
        }                   
        keyboard.SW25 = 0;
    }
    
    // !!! END OF PASTE !!!
}

//white keys only
void keyboard_eight_note(void) {
    
    unsigned char pitch;    //is a pitch
    
    unsigned char *mode_p;  //points to a mode
    
    //selects a mode
    switch (which_mode) {
        case ionian:
            mode_p = ionian_key;
            break;
        case dorian:
            mode_p = dorian_key;
            break;
        case phrygian:
            mode_p = phrygian_key;
            break;
        case lydian:
            mode_p = lydian_key;
            break;
        case mixolydian:
            mode_p = mixolydian_key;
            break;
        case aeolian:
            mode_p = aeolian_key;
            break;
        case locrian:
            mode_p = locrian_key;
            break;
        default:
            break;
    }

    // *** NOTE ON ***
    if((button_state_now & BUTTON_0) && !keyboard.SW1){ //!keyboard.SW1
        pitch = C;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[0],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[0],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[0][0],velocity);
            noteOn(channel,pitch + diatonic_major[0][1],velocity);
            noteOn(channel,pitch + diatonic_major[0][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[0][0],velocity);
            noteOn(channel,diatonic_minor[0][0] + diatonic_minor[0][1],velocity);
            noteOn(channel,diatonic_minor[0][0] + diatonic_minor[0][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[0][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[0][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[0][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[0][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[0][0],velocity);
            noteOn(channel,diatonic_seventh_minor[0][0] + diatonic_seventh_minor[0][1],velocity);
            noteOn(channel,diatonic_seventh_minor[0][0] + diatonic_seventh_minor[0][2],velocity);
            noteOn(channel,diatonic_seventh_minor[0][0] + diatonic_seventh_minor[0][3],velocity);
        }
        keyboard.SW1 = 1;
    }
    if((button_state_now & BUTTON_2) && !keyboard.SW3) {
        pitch = D;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[1],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[1],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[1],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[1][0],velocity);
            noteOn(channel,pitch + diatonic_major[1][1],velocity);
            noteOn(channel,pitch + diatonic_major[1][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[1][0],velocity);
            noteOn(channel,diatonic_minor[1][0] + diatonic_minor[1][1],velocity);
            noteOn(channel,diatonic_minor[1][0] + diatonic_minor[1][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[1][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[1][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[1][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[1][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[1][0],velocity);
            noteOn(channel,diatonic_seventh_minor[1][0] + diatonic_seventh_minor[1][1],velocity);
            noteOn(channel,diatonic_seventh_minor[1][0] + diatonic_seventh_minor[1][2],velocity);
            noteOn(channel,diatonic_seventh_minor[1][0] + diatonic_seventh_minor[1][3],velocity);
        }        
        keyboard.SW3 = 1;
    }
    if((button_state_now & BUTTON_4) && !keyboard.SW5) {
        pitch = E;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[2],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[2],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[2],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[2][0],velocity);
            noteOn(channel,pitch + diatonic_major[2][1],velocity);
            noteOn(channel,pitch + diatonic_major[2][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[2][0],velocity);
            noteOn(channel,diatonic_minor[2][0] + diatonic_minor[2][1],velocity);
            noteOn(channel,diatonic_minor[2][0] + diatonic_minor[2][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[2][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[2][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[2][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[2][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[2][0],velocity);
            noteOn(channel,diatonic_seventh_minor[2][0] + diatonic_seventh_minor[2][1],velocity);
            noteOn(channel,diatonic_seventh_minor[2][0] + diatonic_seventh_minor[2][2],velocity);
            noteOn(channel,diatonic_seventh_minor[2][0] + diatonic_seventh_minor[2][3],velocity);
        }                
        keyboard.SW5 = 1;    
    }              
    if((button_state_now & BUTTON_5) && !keyboard.SW6) {
        pitch = F;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[3],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[3],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[3],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[3][0],velocity);
            noteOn(channel,pitch + diatonic_major[3][1],velocity);
            noteOn(channel,pitch + diatonic_major[3][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[3][0],velocity);
            noteOn(channel,diatonic_minor[3][0] + diatonic_minor[3][1],velocity);
            noteOn(channel,diatonic_minor[3][0] + diatonic_minor[3][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[3][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[3][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[3][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[3][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[3][0],velocity);
            noteOn(channel,diatonic_seventh_minor[3][0] + diatonic_seventh_minor[3][1],velocity);
            noteOn(channel,diatonic_seventh_minor[3][0] + diatonic_seventh_minor[3][2],velocity);
            noteOn(channel,diatonic_seventh_minor[3][0] + diatonic_seventh_minor[3][3],velocity);
        }                
        keyboard.SW6 = 1;
    }
    if((button_state_now & BUTTON_7) && !keyboard.SW8) {
        pitch = G;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[4],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[4],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[4],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[4][0],velocity);
            noteOn(channel,pitch + diatonic_major[4][1],velocity);
            noteOn(channel,pitch + diatonic_major[4][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[4][0],velocity);
            noteOn(channel,diatonic_minor[4][0] + diatonic_minor[4][1],velocity);
            noteOn(channel,diatonic_minor[4][0] + diatonic_minor[4][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[4][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[4][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[4][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[4][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[4][0],velocity);
            noteOn(channel,diatonic_seventh_minor[4][0] + diatonic_seventh_minor[4][1],velocity);
            noteOn(channel,diatonic_seventh_minor[4][0] + diatonic_seventh_minor[4][2],velocity);
            noteOn(channel,diatonic_seventh_minor[4][0] + diatonic_seventh_minor[4][3],velocity);
        }                
        keyboard.SW8 = 1;
    }
    if((button_state_now & BUTTON_9) && !keyboard.SW10) {
        pitch = A;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[5],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[5],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[5],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[5][0],velocity);
            noteOn(channel,pitch + diatonic_major[5][1],velocity);
            noteOn(channel,pitch + diatonic_major[5][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[5][0],velocity);
            noteOn(channel,diatonic_minor[5][0] + diatonic_minor[5][1],velocity);
            noteOn(channel,diatonic_minor[5][0] + diatonic_minor[5][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[5][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[5][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[5][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[5][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[5][0],velocity);
            noteOn(channel,diatonic_seventh_minor[5][0] + diatonic_seventh_minor[5][1],velocity);
            noteOn(channel,diatonic_seventh_minor[5][0] + diatonic_seventh_minor[5][2],velocity);
            noteOn(channel,diatonic_seventh_minor[5][0] + diatonic_seventh_minor[5][3],velocity);
        }                
        keyboard.SW10 = 1;
    }
    if((button_state_now & BUTTON_11) && !keyboard.SW12) {
        pitch = B;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[6],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[6],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[6],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[6][0],velocity);
            noteOn(channel,pitch + diatonic_major[6][1],velocity);
            noteOn(channel,pitch + diatonic_major[6][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[6][0],velocity);
            noteOn(channel,diatonic_minor[6][0] + diatonic_minor[6][1],velocity);
            noteOn(channel,diatonic_minor[6][0] + diatonic_minor[6][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[6][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[6][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[6][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[6][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[6][0],velocity);
            noteOn(channel,diatonic_seventh_minor[6][0] + diatonic_seventh_minor[6][1],velocity);
            noteOn(channel,diatonic_seventh_minor[6][0] + diatonic_seventh_minor[6][2],velocity);
            noteOn(channel,diatonic_seventh_minor[6][0] + diatonic_seventh_minor[6][3],velocity);
        }                
        keyboard.SW12 = 1;
    }
    if((button_state_now & BUTTON_12) && !keyboard.SW13) {
        pitch = C2;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[7],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[7],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[7],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[7][0],velocity);
            noteOn(channel,pitch + diatonic_major[7][1],velocity);
            noteOn(channel,pitch + diatonic_major[7][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[7][0],velocity);
            noteOn(channel,diatonic_minor[7][0] + diatonic_minor[7][1],velocity);
            noteOn(channel,diatonic_minor[7][0] + diatonic_minor[7][2],velocity);
            //noteOn(channel,diatonic_minor[7][1],velocity);
            //noteOn(channel,diatonic_minor[7][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[7][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[7][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[7][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[7][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[7][0],velocity);
            noteOn(channel,diatonic_seventh_minor[7][0] + diatonic_seventh_minor[7][1],velocity);
            noteOn(channel,diatonic_seventh_minor[7][0] + diatonic_seventh_minor[7][2],velocity);
            noteOn(channel,diatonic_seventh_minor[7][0] + diatonic_seventh_minor[7][3],velocity);
        }         
        keyboard.SW13 = 1;
    }
 
    //!!! PASTE 2ND OCTAVE HERE (NOTE ON) !!!
    
    if((button_state_now & BUTTON_14) && !keyboard.SW15){ //!keyboard.SW1
        pitch = D2;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[8],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[8],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[8],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[8][0],velocity);
            noteOn(channel,pitch + diatonic_major[8][1],velocity);
            noteOn(channel,pitch + diatonic_major[8][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[8][0],velocity);
            //noteOn(channel,diatonic_minor[8][1],velocity);
            //noteOn(channel,diatonic_minor[8][2],velocity);
            noteOn(channel,diatonic_minor[8][0] + diatonic_minor[8][1],velocity);
            noteOn(channel,diatonic_minor[8][0] + diatonic_minor[8][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[8][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[8][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[8][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[8][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[8][0],velocity);
            noteOn(channel,diatonic_seventh_minor[8][0] + diatonic_seventh_minor[8][1],velocity);
            noteOn(channel,diatonic_seventh_minor[8][0] + diatonic_seventh_minor[8][2],velocity);
            noteOn(channel,diatonic_seventh_minor[8][0] + diatonic_seventh_minor[8][3],velocity);
        }
        keyboard.SW15 = 1;
    }
    if((button_state_now & BUTTON_16) && !keyboard.SW17) {
        pitch = E2;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[9],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[9],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[9],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[9][0],velocity);
            noteOn(channel,pitch + diatonic_major[9][1],velocity);
            noteOn(channel,pitch + diatonic_major[9][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[9][0],velocity);
            //noteOn(channel,diatonic_minor[9][1],velocity);
            //noteOn(channel,diatonic_minor[9][2],velocity);
            noteOn(channel,diatonic_minor[9][0] + diatonic_minor[9][1],velocity);
            noteOn(channel,diatonic_minor[9][0] + diatonic_minor[9][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[9][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[9][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[9][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[9][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[9][0],velocity);
            noteOn(channel,diatonic_seventh_minor[9][0] + diatonic_seventh_minor[9][1],velocity);
            noteOn(channel,diatonic_seventh_minor[9][0] + diatonic_seventh_minor[9][2],velocity);
            noteOn(channel,diatonic_seventh_minor[9][0] + diatonic_seventh_minor[9][3],velocity);
        }        
        keyboard.SW17 = 1;
    }
    if((button_state_now & BUTTON_17) && !keyboard.SW18) {
        pitch = F2;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[10],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[10],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[10],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[10][0],velocity);
            noteOn(channel,pitch + diatonic_major[10][1],velocity);
            noteOn(channel,pitch + diatonic_major[10][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[10][0],velocity);
            //noteOn(channel,diatonic_minor[10][1],velocity);
            //noteOn(channel,diatonic_minor[10][2],velocity);
            noteOn(channel,diatonic_minor[10][0] + diatonic_minor[10][1],velocity);
            noteOn(channel,diatonic_minor[10][0] + diatonic_minor[10][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[10][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[10][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[10][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[10][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[10][0],velocity);
            noteOn(channel,diatonic_seventh_minor[10][0] + diatonic_seventh_minor[10][1],velocity);
            noteOn(channel,diatonic_seventh_minor[10][0] + diatonic_seventh_minor[10][2],velocity);
            noteOn(channel,diatonic_seventh_minor[10][0] + diatonic_seventh_minor[10][3],velocity);
        }                
        keyboard.SW18 = 1;    
    }              
    if((button_state_now & BUTTON_19) && !keyboard.SW20) {
        pitch = G2;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[11],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[11],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[11],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[11][0],velocity);
            noteOn(channel,pitch + diatonic_major[11][1],velocity);
            noteOn(channel,pitch + diatonic_major[11][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[11][0],velocity);
            //noteOn(channel,diatonic_minor[11][1],velocity);
            //noteOn(channel,diatonic_minor[11][2],velocity);
            noteOn(channel,diatonic_minor[11][0] + diatonic_minor[11][1],velocity);
            noteOn(channel,diatonic_minor[11][0] + diatonic_minor[11][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[11][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[11][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[11][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[11][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[11][0],velocity);
            noteOn(channel,diatonic_seventh_minor[11][0] + diatonic_seventh_minor[11][1],velocity);
            noteOn(channel,diatonic_seventh_minor[11][0] + diatonic_seventh_minor[11][2],velocity);
            noteOn(channel,diatonic_seventh_minor[11][0] + diatonic_seventh_minor[11][3],velocity);
        }                
        keyboard.SW20 = 1;
    }
    if((button_state_now & BUTTON_21) && !keyboard.SW22) {
        pitch = A2;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[12],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[12],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[12],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[12][0],velocity);
            noteOn(channel,pitch + diatonic_major[12][1],velocity);
            noteOn(channel,pitch + diatonic_major[12][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[12][0],velocity);
            //noteOn(channel,diatonic_minor[12][1],velocity);
            //noteOn(channel,diatonic_minor[12][2],velocity);
            noteOn(channel,diatonic_minor[12][0] + diatonic_minor[12][1],velocity);
            noteOn(channel,diatonic_minor[12][0] + diatonic_minor[12][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[12][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[12][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[12][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[12][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[12][0],velocity);
            noteOn(channel,diatonic_seventh_minor[12][0] + diatonic_seventh_minor[12][1],velocity);
            noteOn(channel,diatonic_seventh_minor[12][0] + diatonic_seventh_minor[12][2],velocity);
            noteOn(channel,diatonic_seventh_minor[12][0] + diatonic_seventh_minor[12][3],velocity);
        }                
        keyboard.SW22 = 1;
    }
    if((button_state_now & BUTTON_23) && !keyboard.SW24) {
        pitch = B2;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[13],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[13],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[13],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOn(channel,pitch + diatonic_major[13][0],velocity);
            noteOn(channel,pitch + diatonic_major[13][1],velocity);
            noteOn(channel,pitch + diatonic_major[13][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOn(channel,diatonic_minor[13][0],velocity);
            //noteOn(channel,diatonic_minor[13][1],velocity);
            //noteOn(channel,diatonic_minor[13][2],velocity);
            noteOn(channel,diatonic_minor[13][0] + diatonic_minor[13][1],velocity);
            noteOn(channel,diatonic_minor[13][0] + diatonic_minor[13][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOn(channel,pitch + diatonic_seventh_major[13][0],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[13][1],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[13][2],velocity);
            noteOn(channel,pitch + diatonic_seventh_major[13][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOn(channel,diatonic_seventh_minor[13][0],velocity);
            noteOn(channel,diatonic_seventh_minor[13][0] + diatonic_seventh_minor[13][1],velocity);
            noteOn(channel,diatonic_seventh_minor[13][0] + diatonic_seventh_minor[13][2],velocity);
            noteOn(channel,diatonic_seventh_minor[13][0] + diatonic_seventh_minor[13][3],velocity);
        }                
        keyboard.SW24 = 1;
    }

    if((button_state_now & BUTTON_24) && !keyboard.SW25) {
        pitch = C3;
        if(KEYBOARD_MODE == MAJOR) {noteOn(channel,major_key[14],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOn(channel,minor_key[14],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOn(channel,mode_p[0] + mode_p[14],velocity);}
        keyboard.SW25 = 1;
    }    
    
    // !!! END OF PASTE !!!
    
    // *** NOTE OFF ***
    if(((button_state_last & BUTTON_0)) && ((button_state_now & BUTTON_0) == 0) && keyboard.SW1) {
        pitch = C;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[0],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[0],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,diatonic_major[0][0],velocity);
            noteOff(channel,diatonic_major[0][1],velocity);
            noteOff(channel,diatonic_major[0][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[0][0],velocity);
            noteOff(channel,diatonic_minor[0][0] + diatonic_minor[0][1],velocity);
            noteOff(channel,diatonic_minor[0][0] + diatonic_minor[0][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[0][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[0][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[0][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[0][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[0][0],velocity);
            noteOff(channel,diatonic_seventh_minor[0][0] + diatonic_seventh_minor[0][1],velocity);
            noteOff(channel,diatonic_seventh_minor[0][0] + diatonic_seventh_minor[0][2],velocity);
            noteOff(channel,diatonic_seventh_minor[0][0] + diatonic_seventh_minor[0][3],velocity);
        }        
        keyboard.SW1 = 0;
    }
    if(((button_state_last & BUTTON_2)) && ((button_state_now & BUTTON_2) == 0) && keyboard.SW3) {
        pitch = D;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[1],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[1],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[1],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[1][0],velocity);
            noteOff(channel,pitch + diatonic_major[1][1],velocity);
            noteOff(channel,pitch + diatonic_major[1][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[1][0],velocity);
            noteOff(channel,diatonic_minor[1][0] + diatonic_minor[1][1],velocity);
            noteOff(channel,diatonic_minor[1][0] + diatonic_minor[1][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[1][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[1][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[1][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[1][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[1][0],velocity);
            noteOff(channel,diatonic_seventh_minor[1][0] + diatonic_seventh_minor[1][1],velocity);
            noteOff(channel,diatonic_seventh_minor[1][0] + diatonic_seventh_minor[1][2],velocity);
            noteOff(channel,diatonic_seventh_minor[1][0] + diatonic_seventh_minor[1][3],velocity);
        }        
        keyboard.SW3 = 0;
    }
    if(((button_state_last & BUTTON_4)) && ((button_state_now & BUTTON_4) == 0) && keyboard.SW5) {
        pitch = E;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[2],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[2],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[2],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[2][0],velocity);
            noteOff(channel,pitch + diatonic_major[2][1],velocity);
            noteOff(channel,pitch + diatonic_major[2][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[2][0],velocity);
            noteOff(channel,diatonic_minor[2][0] + diatonic_minor[2][1],velocity);
            noteOff(channel,diatonic_minor[2][0] + diatonic_minor[2][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[2][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[2][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[2][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[2][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[2][0],velocity);
            noteOff(channel,diatonic_seventh_minor[2][0] + diatonic_seventh_minor[2][1],velocity);
            noteOff(channel,diatonic_seventh_minor[2][0] + diatonic_seventh_minor[2][2],velocity);
            noteOff(channel,diatonic_seventh_minor[2][0] + diatonic_seventh_minor[2][3],velocity);
        }        
        keyboard.SW5 = 0;
    }
    if(((button_state_last & BUTTON_5)) && ((button_state_now & BUTTON_5) == 0) && keyboard.SW6) {
        pitch = F;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[3],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[3],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[3],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[3][0],velocity);
            noteOff(channel,pitch + diatonic_major[3][1],velocity);
            noteOff(channel,pitch + diatonic_major[3][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[3][0],velocity);
            noteOff(channel,diatonic_minor[3][0] + diatonic_minor[3][1],velocity);
            noteOff(channel,diatonic_minor[3][0] + diatonic_minor[3][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[3][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[3][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[3][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[3][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[3][0],velocity);
            noteOff(channel,diatonic_seventh_minor[3][0] + diatonic_seventh_minor[3][1],velocity);
            noteOff(channel,diatonic_seventh_minor[3][0] + diatonic_seventh_minor[3][2],velocity);
            noteOff(channel,diatonic_seventh_minor[3][0] + diatonic_seventh_minor[3][3],velocity);
        }        
        keyboard.SW6 = 0;
    }
    if(((button_state_last & BUTTON_7)) && ((button_state_now & BUTTON_7) == 0) && keyboard.SW8) {
        pitch = G;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[4],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[4],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[4],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[4][0],velocity);
            noteOff(channel,pitch + diatonic_major[4][1],velocity);
            noteOff(channel,pitch + diatonic_major[4][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[4][0],velocity);
            noteOff(channel,diatonic_minor[4][0] + diatonic_minor[4][1],velocity);
            noteOff(channel,diatonic_minor[4][0] + diatonic_minor[4][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[4][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[4][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[4][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[4][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[4][0],velocity);
            noteOff(channel,diatonic_seventh_minor[4][0] + diatonic_seventh_minor[4][1],velocity);
            noteOff(channel,diatonic_seventh_minor[4][0] + diatonic_seventh_minor[4][2],velocity);
            noteOff(channel,diatonic_seventh_minor[4][0] + diatonic_seventh_minor[4][3],velocity);
        }        
        keyboard.SW8 = 0;
    }
    if(((button_state_last & BUTTON_9)) && ((button_state_now & BUTTON_9) == 0) && keyboard.SW10) {
        pitch = A;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[5],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[5],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[5],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[5][0],velocity);
            noteOff(channel,pitch + diatonic_major[5][1],velocity);
            noteOff(channel,pitch + diatonic_major[5][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[5][0],velocity);
            noteOff(channel,diatonic_minor[5][0] + diatonic_minor[5][1],velocity);
            noteOff(channel,diatonic_minor[5][0] + diatonic_minor[5][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[5][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[5][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[5][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[5][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[5][0],velocity);
            noteOff(channel,diatonic_seventh_minor[5][0] + diatonic_seventh_minor[5][1],velocity);
            noteOff(channel,diatonic_seventh_minor[5][0] + diatonic_seventh_minor[5][2],velocity);
            noteOff(channel,diatonic_seventh_minor[5][0] + diatonic_seventh_minor[5][3],velocity);
        }        
        keyboard.SW10 = 0;
    }
    if(((button_state_last & BUTTON_11)) && ((button_state_now & BUTTON_11) == 0) && keyboard.SW12) {
        pitch = B;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[6],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[6],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[6],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[6][0],velocity);
            noteOff(channel,pitch + diatonic_major[6][1],velocity);
            noteOff(channel,pitch + diatonic_major[6][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[6][0],velocity);
            noteOff(channel,diatonic_minor[6][0] + diatonic_minor[6][1],velocity);
            noteOff(channel,diatonic_minor[6][0] + diatonic_minor[6][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[6][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[6][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[6][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[6][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[6][0],velocity);
            noteOff(channel,diatonic_seventh_minor[6][0] + diatonic_seventh_minor[6][1],velocity);
            noteOff(channel,diatonic_seventh_minor[6][0] + diatonic_seventh_minor[6][2],velocity);
            noteOff(channel,diatonic_seventh_minor[6][0] + diatonic_seventh_minor[6][3],velocity);
        }        
        keyboard.SW12 = 0;
    }
    
    if(((button_state_last & BUTTON_12)) && ((button_state_now & BUTTON_12) == 0) && keyboard.SW13) {
        pitch = C2;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[7],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[7],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[7],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[7][0],velocity);
            noteOff(channel,pitch + diatonic_major[7][1],velocity);
            noteOff(channel,pitch + diatonic_major[7][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[7][0],velocity);
            noteOff(channel,diatonic_minor[7][0] + diatonic_minor[7][1],velocity);
            noteOff(channel,diatonic_minor[7][0] + diatonic_minor[7][2],velocity);
            //noteOff(channel,diatonic_minor[7][1],velocity);
            //noteOff(channel,diatonic_minor[7][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[7][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[7][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[7][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[7][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[7][0],velocity);
            noteOff(channel,diatonic_seventh_minor[7][0] + diatonic_seventh_minor[7][1],velocity);
            noteOff(channel,diatonic_seventh_minor[7][0] + diatonic_seventh_minor[7][2],velocity);
            noteOff(channel,diatonic_seventh_minor[7][0] + diatonic_seventh_minor[7][3],velocity);
        }         
        keyboard.SW13 = 0;
    }
    
    //!!! PASTE 2ND OCTAVE HERE (NOTE ON) !!!

    if(((button_state_last & BUTTON_14)) && ((button_state_now & BUTTON_14) == 0) && keyboard.SW15) {
        pitch = D2;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[8],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[8],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[8],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[8][0],velocity);
            noteOff(channel,pitch + diatonic_major[8][1],velocity);
            noteOff(channel,pitch + diatonic_major[8][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[8][0],velocity);
            //noteOff(channel,diatonic_minor[8][1],velocity);
            //noteOff(channel,diatonic_minor[8][2],velocity);
            noteOff(channel,diatonic_minor[8][0] + diatonic_minor[8][1],velocity);
            noteOff(channel,diatonic_minor[8][0] + diatonic_minor[8][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[8][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[8][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[8][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[8][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[8][0],velocity);
            noteOff(channel,diatonic_seventh_minor[8][0] + diatonic_seventh_minor[8][1],velocity);
            noteOff(channel,diatonic_seventh_minor[8][0] + diatonic_seventh_minor[8][2],velocity);
            noteOff(channel,diatonic_seventh_minor[8][0] + diatonic_seventh_minor[8][3],velocity);
        }
        keyboard.SW15 = 0;
    }
    
    if(((button_state_last & BUTTON_16)) && ((button_state_now & BUTTON_16) == 0) && keyboard.SW17) {
        pitch = E2;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[9],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[9],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[9],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[9][0],velocity);
            noteOff(channel,pitch + diatonic_major[9][1],velocity);
            noteOff(channel,pitch + diatonic_major[9][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[9][0],velocity);
            //noteOff(channel,diatonic_minor[9][1],velocity);
            //noteOff(channel,diatonic_minor[9][2],velocity);
            noteOff(channel,diatonic_minor[9][0] + diatonic_minor[9][1],velocity);
            noteOff(channel,diatonic_minor[9][0] + diatonic_minor[9][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[9][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[9][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[9][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[9][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[9][0],velocity);
            noteOff(channel,diatonic_seventh_minor[9][0] + diatonic_seventh_minor[9][1],velocity);
            noteOff(channel,diatonic_seventh_minor[9][0] + diatonic_seventh_minor[9][2],velocity);
            noteOff(channel,diatonic_seventh_minor[9][0] + diatonic_seventh_minor[9][3],velocity);
        }        
        keyboard.SW17 = 0;
    }
    if(((button_state_last & BUTTON_17)) && ((button_state_now & BUTTON_17) == 0) && keyboard.SW18) {
        pitch = F2;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[10],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[10],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[10],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[10][0],velocity);
            noteOff(channel,pitch + diatonic_major[10][1],velocity);
            noteOff(channel,pitch + diatonic_major[10][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[10][0],velocity);
            //noteOff(channel,diatonic_minor[10][1],velocity);
            //noteOff(channel,diatonic_minor[10][2],velocity);
            noteOff(channel,diatonic_minor[10][0] + diatonic_minor[10][1],velocity);
            noteOff(channel,diatonic_minor[10][0] + diatonic_minor[10][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[10][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[10][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[10][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[10][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[10][0],velocity);
            noteOff(channel,diatonic_seventh_minor[10][0] + diatonic_seventh_minor[10][1],velocity);
            noteOff(channel,diatonic_seventh_minor[10][0] + diatonic_seventh_minor[10][2],velocity);
            noteOff(channel,diatonic_seventh_minor[10][0] + diatonic_seventh_minor[10][3],velocity);
        }                
        keyboard.SW18 = 0;    
    }              
    if(((button_state_last & BUTTON_19)) && ((button_state_now & BUTTON_19) == 0) && keyboard.SW20) {
        pitch = G2;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[11],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[11],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[11],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[11][0],velocity);
            noteOff(channel,pitch + diatonic_major[11][1],velocity);
            noteOff(channel,pitch + diatonic_major[11][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[11][0],velocity);
            //noteOff(channel,diatonic_minor[11][1],velocity);
            //noteOff(channel,diatonic_minor[11][2],velocity);
            noteOff(channel,diatonic_minor[11][0] + diatonic_minor[11][1],velocity);
            noteOff(channel,diatonic_minor[11][0] + diatonic_minor[11][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[11][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[11][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[11][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[11][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[11][0],velocity);
            noteOff(channel,diatonic_seventh_minor[11][0] + diatonic_seventh_minor[11][1],velocity);
            noteOff(channel,diatonic_seventh_minor[11][0] + diatonic_seventh_minor[11][2],velocity);
            noteOff(channel,diatonic_seventh_minor[11][0] + diatonic_seventh_minor[11][3],velocity);
        }                
        keyboard.SW20 = 0;
    }
    if(((button_state_last & BUTTON_21)) && ((button_state_now & BUTTON_21) == 0) && keyboard.SW22) {
        pitch = A2;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[12],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[12],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[12],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[12][0],velocity);
            noteOff(channel,pitch + diatonic_major[12][1],velocity);
            noteOff(channel,pitch + diatonic_major[12][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[12][0],velocity);
            //noteOff(channel,diatonic_minor[12][1],velocity);
            //noteOff(channel,diatonic_minor[12][2],velocity);
            noteOff(channel,diatonic_minor[12][0] + diatonic_minor[12][1],velocity);
            noteOff(channel,diatonic_minor[12][0] + diatonic_minor[12][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[12][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[12][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[12][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[12][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[124][0],velocity);
            noteOff(channel,diatonic_seventh_minor[12][0] + diatonic_seventh_minor[12][1],velocity);
            noteOff(channel,diatonic_seventh_minor[12][0] + diatonic_seventh_minor[12][2],velocity);
            noteOff(channel,diatonic_seventh_minor[12][0] + diatonic_seventh_minor[12][3],velocity);
        }                
        keyboard.SW22 = 0;
    }
    if(((button_state_last & BUTTON_23)) && ((button_state_now & BUTTON_23) == 0) && keyboard.SW24) {
        pitch = B2;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[13],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[13],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[13],velocity);}
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) {
            noteOff(channel,pitch + diatonic_major[13][0],velocity);
            noteOff(channel,pitch + diatonic_major[13][1],velocity);
            noteOff(channel,pitch + diatonic_major[13][2],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_TRIAD_MINOR) {
            noteOff(channel,diatonic_minor[13][0],velocity);
            //noteOff(channel,diatonic_minor[13][1],velocity);
            //noteOff(channel,diatonic_minor[13][2],velocity);
            noteOff(channel,diatonic_minor[13][0] + diatonic_minor[13][1],velocity);
            noteOff(channel,diatonic_minor[13][0] + diatonic_minor[13][2],velocity);            
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MAJOR) {
            noteOff(channel,pitch + diatonic_seventh_major[13][0],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[13][1],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[13][2],velocity);
            noteOff(channel,pitch + diatonic_seventh_major[13][3],velocity);
        }
        if(KEYBOARD_MODE == DIATONIC_7TH_MINOR) {
            noteOff(channel,diatonic_seventh_minor[13][0],velocity);
            noteOff(channel,diatonic_seventh_minor[13][0] + diatonic_seventh_minor[13][1],velocity);
            noteOff(channel,diatonic_seventh_minor[13][0] + diatonic_seventh_minor[13][2],velocity);
            noteOff(channel,diatonic_seventh_minor[13][0] + diatonic_seventh_minor[13][3],velocity);
        }                
        keyboard.SW24 = 0;
    }

    if(((button_state_last & BUTTON_24)) && ((button_state_now & BUTTON_24) == 0) && keyboard.SW25) {
        pitch = C3;
        if(KEYBOARD_MODE == MAJOR) {noteOff(channel,major_key[14],velocity);}
        if(KEYBOARD_MODE == MINOR) {noteOff(channel,minor_key[14],velocity);}
        if(KEYBOARD_MODE == MODES) {noteOff(channel,mode_p[0] + mode_p[14],velocity);}
        keyboard.SW25 = 0;
    }    
    

    // !!! END OF PASTE !!!
}
