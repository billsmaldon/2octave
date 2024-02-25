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

#include "drum.h"

//drum channel note on/note off/control change
void processDrumpad(void) {

    //DRUM NOTE_ON
    //if(((drum_button_state_now) & DRUM_BUTTON_0) && !drum.SW1){
    if((drum_button_state_now & DRUM_BUTTON_0) && !(button_state_now & BUTTON_27) && !drum.SW1){
        drum.SW1 = 1;
        if (DRUM_MODE == NOTE) {noteOnDrum(drumchannel,DRUM_NOTE[0],velocity);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TRIGGER) {controlChange(channel,DRUM_CC[0], DRUM_CC_ON);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TOGGLE & toggle_state.T1 == 0) {controlChange(channel,DRUM_CC[0], DRUM_CC_ON);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TOGGLE & toggle_state.T1 == 1) {controlChange(channel,DRUM_CC[0], DRUM_CC_OFF);}
        toggle_state.T1 ^= 1;
    }
    if(((drum_button_state_now) & DRUM_BUTTON_1) && !(button_state_now & BUTTON_27) && !drum.SW2) {
        drum.SW2 = 1;
        if (DRUM_MODE == NOTE) {noteOnDrum(drumchannel,DRUM_NOTE[1],velocity);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TRIGGER) {controlChange(channel,DRUM_CC[1], DRUM_CC_ON);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TOGGLE & toggle_state.T2 == 0) {controlChange(channel,DRUM_CC[1], DRUM_CC_ON);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TOGGLE & toggle_state.T2 == 1) {controlChange(channel,DRUM_CC[1], DRUM_CC_OFF);}
        toggle_state.T2 ^= 1;
    }
    if(((drum_button_state_now) & DRUM_BUTTON_2) && !(button_state_now & BUTTON_27) && !drum.SW3) {
        drum.SW3 = 1;
        if (DRUM_MODE == NOTE) {noteOnDrum(drumchannel,DRUM_NOTE[2],velocity);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TRIGGER) {controlChange(channel,DRUM_CC[2], DRUM_CC_ON);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TOGGLE & toggle_state.T3 == 0) {controlChange(channel,DRUM_CC[2], DRUM_CC_ON);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TOGGLE & toggle_state.T3 == 1) {controlChange(channel,DRUM_CC[2], DRUM_CC_OFF);}
        toggle_state.T3 ^= 1;    
    }
    if(((drum_button_state_now) & DRUM_BUTTON_3) && !(button_state_now & BUTTON_27) && !drum.SW4) {
        drum.SW4 = 1;
        if (DRUM_MODE == NOTE) {noteOnDrum(drumchannel,DRUM_NOTE[3],velocity);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TRIGGER) {controlChange(channel,DRUM_CC[3], DRUM_CC_ON);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TOGGLE & toggle_state.T4 == 0) {controlChange(channel,DRUM_CC[3], DRUM_CC_ON);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TOGGLE & toggle_state.T4 == 1) {controlChange(channel,DRUM_CC[3], DRUM_CC_OFF);}
        toggle_state.T4 ^= 1;
    }
    if(((drum_button_state_now) & DRUM_BUTTON_4) && !(button_state_now & BUTTON_27) && !drum.SW5){
        drum.SW5 = 1;
        if (DRUM_MODE == NOTE) {noteOnDrum(drumchannel,DRUM_NOTE[4],velocity);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TRIGGER) {controlChange(channel,DRUM_CC[4], DRUM_CC_ON);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TOGGLE & toggle_state.T5 == 0) {controlChange(channel,DRUM_CC[4], DRUM_CC_ON);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TOGGLE & toggle_state.T5 == 1) {controlChange(channel,DRUM_CC[4], DRUM_CC_OFF);}
        toggle_state.T5 ^= 1;
    }
    if(((drum_button_state_now) & DRUM_BUTTON_5) && !(button_state_now & BUTTON_27) && !drum.SW6) {
        drum.SW6 = 1;
        if (DRUM_MODE == NOTE) {noteOnDrum(drumchannel,DRUM_NOTE[5],velocity);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TRIGGER) {controlChange(channel,DRUM_CC[5], DRUM_CC_ON);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TOGGLE & toggle_state.T6 == 0) {controlChange(channel,DRUM_CC[5], DRUM_CC_ON);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TOGGLE & toggle_state.T6 == 1) {controlChange(channel,DRUM_CC[5], DRUM_CC_OFF);}
        toggle_state.T6 ^= 1;
    }
    if(((drum_button_state_now) & DRUM_BUTTON_6) && !(button_state_now & BUTTON_27) && !drum.SW7) {
        drum.SW7 = 1;
        if (DRUM_MODE == NOTE) {noteOnDrum(drumchannel,DRUM_NOTE[6],velocity);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TRIGGER) {controlChange(channel,DRUM_CC[6], DRUM_CC_ON);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TOGGLE & toggle_state.T7 == 0) {controlChange(channel,DRUM_CC[6], DRUM_CC_ON);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TOGGLE & toggle_state.T7 == 1) {controlChange(channel,DRUM_CC[6], DRUM_CC_OFF);}
        toggle_state.T7 ^= 1;    
    }
    if(((drum_button_state_now) & DRUM_BUTTON_7) && !(button_state_now & BUTTON_27) && !drum.SW8) {
        drum.SW8 = 1;
        if (DRUM_MODE == NOTE) {noteOnDrum(drumchannel,DRUM_NOTE[7],velocity);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TRIGGER) {controlChange(channel,DRUM_CC[7], DRUM_CC_ON);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TOGGLE & toggle_state.T8 == 0) {controlChange(channel,DRUM_CC[7], DRUM_CC_ON);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TOGGLE & toggle_state.T8 == 1) {controlChange(channel,DRUM_CC[7], DRUM_CC_OFF);}
        toggle_state.T8 ^= 1;
    }    
    
    //DRUM NOTE_OFF
    if(((drum_button_state_last & DRUM_BUTTON_0)) && ((drum_button_state_now & DRUM_BUTTON_0) == 0) && drum.SW1) {
        drum.SW1 = 0;
        if (DRUM_MODE == NOTE) {noteOffDrum(drumchannel,DRUM_NOTE[0],velocity);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TRIGGER) {controlChange(channel,DRUM_CC[0], DRUM_CC_OFF);}
    }
    if(((drum_button_state_last & DRUM_BUTTON_1)) && ((drum_button_state_now & DRUM_BUTTON_1) == 0) && drum.SW2) {
        drum.SW2 = 0;
        if (DRUM_MODE == NOTE) {noteOffDrum(drumchannel,DRUM_NOTE[1],velocity);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TRIGGER) {controlChange(channel,DRUM_CC[1], DRUM_CC_OFF);}
    }        
    if(((drum_button_state_last & DRUM_BUTTON_2)) && ((drum_button_state_now & DRUM_BUTTON_2) == 0) && drum.SW3) {
        drum.SW3 = 0;
        if (DRUM_MODE == NOTE) {noteOffDrum(drumchannel,DRUM_NOTE[2],velocity);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TRIGGER) {controlChange(channel,DRUM_CC[2], DRUM_CC_OFF);}
    }
    if(((drum_button_state_last & DRUM_BUTTON_3)) && ((drum_button_state_now & DRUM_BUTTON_3) == 0) && drum.SW4) {
        drum.SW4 = 0;
        if (DRUM_MODE == NOTE) {noteOffDrum(drumchannel,DRUM_NOTE[3],velocity);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TRIGGER) {controlChange(channel,DRUM_CC[3], DRUM_CC_OFF);}
    }    
    if(((drum_button_state_last & DRUM_BUTTON_4)) && ((drum_button_state_now & DRUM_BUTTON_4) == 0) && drum.SW5) {
        drum.SW5 = 0;
        if (DRUM_MODE == NOTE) {noteOffDrum(drumchannel,DRUM_NOTE[4],velocity);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TRIGGER) {controlChange(channel,DRUM_CC[4], DRUM_CC_OFF);}
    }
    if(((drum_button_state_last & DRUM_BUTTON_5)) && ((drum_button_state_now & DRUM_BUTTON_5) == 0) && drum.SW6) {
        drum.SW6 = 0;
        if (DRUM_MODE == NOTE) {noteOffDrum(drumchannel,DRUM_NOTE[5],velocity);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TRIGGER) {controlChange(channel,DRUM_CC[5], DRUM_CC_OFF);}
    }        
    if(((drum_button_state_last & DRUM_BUTTON_6)) && ((drum_button_state_now & DRUM_BUTTON_6) == 0) && drum.SW7) {
        drum.SW7 = 0;
        if (DRUM_MODE == NOTE) {noteOffDrum(drumchannel,DRUM_NOTE[6],velocity);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TRIGGER) {controlChange(channel,DRUM_CC[6], DRUM_CC_OFF);}
    }
    if(((drum_button_state_last & DRUM_BUTTON_7)) && ((drum_button_state_now & DRUM_BUTTON_7) == 0) && drum.SW8) {
        drum.SW8 = 0;
        if (DRUM_MODE == NOTE) {noteOffDrum(drumchannel,DRUM_NOTE[7],velocity);}
        if (DRUM_MODE == CONTROL & CONTROL_MODE == TRIGGER) {controlChange(channel,DRUM_CC[7], DRUM_CC_OFF);}
    }    
}

