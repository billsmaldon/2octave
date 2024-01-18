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

#include "arpeggio.h"

void wait_one_pulse (unsigned char mode){

    lastNoteMode = mode;    //immediate or finishLast
    
    //delay of 'immediate' (no delay)
    if(lastNoteMode == immediate) {
        finishLastNote = 0;     //clear finishLastNote
        TIMER_OVERFLOWS = 0;    //make next noteOn() immediate (after key release)
        return;
    }
    
    //delay of 'finishLast' (one note length delay)
    if(lastNoteMode == finishLast) {
        finishLastNote = 1;     //set finishLastNote
        TMR0ON = 1;             //turn TIMER0 on
        while(finishLastNote == 1){;}   //poll finishLastNote until cleared in ISR
    }
}

void add_notes_to_arpeggio(unsigned char pitch){
    
    /* ADD NOTES TO ARPEGGIO HERE */
    
    if(ARRAY_INDEX > (MAX_NUM_NOTES - 1)){
        ARRAY_INDEX = MAX_NUM_NOTES - 1;
        rotateArrayLeft(0);
        ARPEGGIO[MAX_NUM_NOTES - 1] = pitch;
    }    
    
    if(ARRAY_INDEX <= (MAX_NUM_NOTES - 1)){
        //assign pitch to ARPEGGIO[ARRAY_INDEX]
        ARPEGGIO[ARRAY_INDEX] = pitch;
        //next array index
        ARRAY_INDEX++;
    }

    //increase number of notes pressed
    NUM_NOTES_PRESSED++;         
    //limit num notes pressed to max num notes
    if(NUM_NOTES_PRESSED > MAX_NUM_NOTES){NUM_NOTES_PRESSED = MAX_NUM_NOTES;}
    
}

void delete_notes_from_arpeggio(unsigned char pitch) {
    
    //find array index of key released
    signed char INDEX_TO_SHIFT_LEFT_AT = findArrayIndex(pitch);
    //shift left at point of key release, then NUM_NOTES_PRESSED--
    
    //if(INDEX_TO_SHIFT_LEFT_AT < 0){printThisNumber(9999);return;}
    
    //printThisNumber(INDEX_TO_SHIFT_LEFT_AT);
    
    //this function limited to 8 notes!
    //shiftTheArray(INDEX_TO_SHIFT_LEFT_AT;
    
    //this function unlimited notes!
    rotateArrayLeft(INDEX_TO_SHIFT_LEFT_AT);

    //decrease NUM_NOTES_PRESSED  
    if(NUM_NOTES_PRESSED > 0) {NUM_NOTES_PRESSED--;}
    
    //printThisNumber(NUM_NOTES_PRESSED);  
    
    //reset array index if no notes pressed
    if(NUM_NOTES_PRESSED == 0) {ARRAY_INDEX = 0;} //comment out this one?
    
    //decrease ARRAY_INDEX
    if(ARRAY_INDEX > 0){ARRAY_INDEX--;} //commented out!
    
    // !!! this later !!!
    //if(ARRAY_INDEX >= (MAX_NUM_NOTES - 1)){ARRAY_INDEX = (MAX_NUM_NOTES - 1);}
    //else {ARRAY_INDEX--;}
    
    //printThisNumber(ARRAY_INDEX);
    
}

void finish_arpeggio_setup(void) {

    //reset the arpeggiator on KEY_PRESS, KEY_RELEASE
    if((ON_OFF == 1) && (RESET_ON_KEY_PRESS == 1)){resetArpeggio();}
    if((ON_OFF == 0) && (RESET_ON_KEY_RELEASE == 1)){resetArpeggio();}
    
    //setup the arpeggio type
    setupArpeggio();
    
    TIMER_OVERFLOWS = 0;   //make next noteOn() immediate
}

void key_press_release_note_off(void) {

        //if ARPEGGIO_TYPE was UP_DOWN and now is DOWN_UP:
        if((startingDirection == UP) && (ARPEGGIO_TYPE == DOWN_UP)){stored_octave += (OCTAVES - 1);} //was '2'
        //if ARPEGGIO_TYPE was DOWN_UP and now is UP_DOWN
        if((startingDirection == DOWN) && (ARPEGGIO_TYPE == UP_DOWN)){stored_octave -= (OCTAVES - 1);}
        
        // TRY SETTING THIS TO '1'
        TMR0ON = 0; //TIMER0 off
        //TMR0ON = 1; //TIMER0 off
        
        //store 'last_note'
        static signed char temp;
        temp = last_note;
        
        //calculate the correct octave for the noteOff()
        if((last_note != 0)){
            if(stored_octave == -3){noteOff(channel, temp - ((OCTAVES - (OCTAVES - 3)) * 12), velocity);}
            if(stored_octave == -2){noteOff(channel, temp - ((OCTAVES - (OCTAVES - 2)) * 12), velocity);}
            if(stored_octave == -1){noteOff(channel, temp - ((OCTAVES - (OCTAVES - 1)) * 12), velocity);}
        
            if(stored_octave ==  0){
                noteOff(channel, temp, velocity);
            }
                
            if(stored_octave ==  1){noteOff(channel, temp + ((OCTAVES - (OCTAVES - 1)) * 12), velocity);}
            if(stored_octave ==  2){noteOff(channel, temp + ((OCTAVES - (OCTAVES - 2)) * 12), velocity);}
            if(stored_octave ==  3){noteOff(channel, temp + ((OCTAVES - (OCTAVES - 3)) * 12), velocity);}
            
            note_off_was_sent = 1;
        }
        
        //ALL FIXED! (need both 2 lines below:)
        if((last_note == 0) && (note_off_was_sent == 0) && (keyboard.SW1 == 1)){noteOff(channel, stored_octave * 12, velocity);note_off_was_sent = 1;}
        if((last_note == 0) && (note_off_was_sent == 0)){noteOff(channel, stored_octave * 12, velocity);note_off_was_sent = 1;}
        
        TMR0ON = 1; //TIMER0 on
}

//calculate TIMER_PRELOAD for TIMER0 interrupt
unsigned short calculate_pulse_length(void) {

    //formula:
    //unsigned int tick_m = (BPM * PPQN);
    //double tick_s = tick_m / 60.0f;
    //double s_tick = 1.0f / tick_s;
    
    double s_tick = 1.0 / ((BPM * PPQN) / 60.0);
    return (unsigned short) ((65535.0 - (s_tick * 20000000.0) / ( 4.0 * PRESCALER)) + 0.5);
}

//reset all the playArpeggio() variables
void resetArpeggio(void){
    
    which_note = 0;
    which_octave = 0;
    last_note = 0;
    last_octave = 0;
    overflow = 0;
    octave_overflow = 0;
    
    // fix arpeggio direction on key press/release
    if(ARPEGGIO_TYPE == UP_DOWN && startingDirection == DOWN){
        ARPEGGIO_TYPE = DOWN_UP;
    }
    
    if(ARPEGGIO_TYPE == DOWN_UP && startingDirection == UP){
        ARPEGGIO_TYPE = UP_DOWN;
    }
    
}

//void setupArpeggio(unsigned char which_arpeggio){
void setupArpeggio(void){
    
    //calculate timer preload value for interrupt
    //TIMER_PRELOAD = calculate_pulse_length(); //commented out! re-calculate only when changing BPM!
    
    if(NUM_NOTES_PRESSED == 0){return;} //added this!
    
    //copy ARPEGGIO[] to ARPEGGIO_SORTED[] and ARPEGGIO_RANDOM[]
    copy_array();
    
    //how to randomize the array
    if(ARPEGGIO_TYPE == RANDOM) {random_pitches();}
    if(ARPEGGIO_TYPE == RANDOM_NON_REPEATING) {random_pitches_non_repeating();}
    
    //pointer to array of arpeggio notes and startingDirection
    //if(ARPEGGIO_TYPE == AS_PRESSED){startingDirection = UP;arpeggioPtr = ARPEGGIO;}
    //if(ARPEGGIO_TYPE == UP | ARPEGGIO_TYPE == UP_DOWN){startingDirection = UP;arpeggioPtr = ARPEGGIO_SORTED;}
    //if(ARPEGGIO_TYPE == DOWN | ARPEGGIO_TYPE == DOWN_UP){startingDirection = DOWN;arpeggioPtr = ARPEGGIO_SORTED;}
    //if(ARPEGGIO_TYPE == RANDOM | ARPEGGIO_TYPE == RANDOM_NON_REPEATING){startingDirection = UP;arpeggioPtr = ARPEGGIO_RANDOM;}    
    
    //pointer to array of arpeggio notes
    if(ARPEGGIO_TYPE == AS_PRESSED){arpeggioPtr = ARPEGGIO;}
    if(ARPEGGIO_TYPE == UP | ARPEGGIO_TYPE == UP_DOWN){arpeggioPtr = ARPEGGIO_SORTED;}
    if(ARPEGGIO_TYPE == DOWN | ARPEGGIO_TYPE == DOWN_UP){arpeggioPtr = ARPEGGIO_SORTED;}
    if(ARPEGGIO_TYPE == RANDOM | ARPEGGIO_TYPE == RANDOM_NON_REPEATING){arpeggioPtr = ARPEGGIO_RANDOM;}        
}

void copy_array(void){
    
    if(NUM_NOTES_PRESSED == 0){return;} //if NUM_NOTES_PRESSED == 0, immediately return
    
    //COPY ARRAY TO SORTED ARRAY, RANDOM ARRAY
    for(unsigned char i = 0; i < NUM_NOTES_PRESSED; i++){
        ARPEGGIO_SORTED[i] = ARPEGGIO[i];
        ARPEGGIO_RANDOM[i] = ARPEGGIO[i];
    }
     
}

void sort_pitches(void) {

    if(NUM_NOTES_PRESSED == 0){return;} //added this!
    
    unsigned char a;
    for(unsigned char i = 0; i < NUM_NOTES_PRESSED; ++i){
        for(unsigned char j = i + 1; j < NUM_NOTES_PRESSED; ++j){
            
            //change < to > !!! REVERSES SORT DIRECTION !!!
            // > ASCENDING
            // < DESCENDING
            
            if(SORT_DIRECTION == ASCENDING) {
                if(ARPEGGIO_SORTED[i] > ARPEGGIO_SORTED[j]){ 
                    a = ARPEGGIO_SORTED[i];
                    ARPEGGIO_SORTED[i] = ARPEGGIO_SORTED[j];
                    ARPEGGIO_SORTED[j] = a;
                }
            }
            
            if(SORT_DIRECTION == DESCENDING) {
                if(ARPEGGIO_SORTED[i] < ARPEGGIO_SORTED[j]){ 
                    a = ARPEGGIO_SORTED[i];
                    ARPEGGIO_SORTED[i] = ARPEGGIO_SORTED[j];
                    ARPEGGIO_SORTED[j] = a;
                }
            }
        }
    }
}

//random pitches
void random_pitches(void){
    
    if(NUM_NOTES_PRESSED == 0){return;} //added this!
    
    for (unsigned char i = 0; i < NUM_NOTES_PRESSED; i++){
        unsigned char random_array_index = rand() % (NUM_NOTES_PRESSED);
        ARPEGGIO_RANDOM[i] = ARPEGGIO[random_array_index];
    }
}

//shuffle pitches
void random_pitches_non_repeating(void){
    
    if(NUM_NOTES_PRESSED == 0){return;} //added this!    
    
    for(unsigned char i = 0; i < NUM_NOTES_PRESSED; i++) {    // shuffle array
        unsigned char temp = ARPEGGIO_RANDOM[i];
        unsigned char randomIndex = rand() % NUM_NOTES_PRESSED;
        ARPEGGIO_RANDOM[i] = ARPEGGIO_RANDOM[randomIndex];
        ARPEGGIO_RANDOM[randomIndex] = temp;
    }
}

void playArpeggio(void){

    //do nothing if array is empty
    if(NUM_NOTES_PRESSED == 0){return;}
    
    // CODE USING ARRAY
    //if((overflow == 1) && (which_octave > 0) && (octave_overflow == 0)){noteOff(channel,ARPEGGIO[NUM_NOTES_PRESSED - 1] + ((which_octave - 1) * 12),velocity); overflow = 0;}
    //if(octave_overflow == 1){noteOff(channel,ARPEGGIO[NUM_NOTES_PRESSED - 1] + ((OCTAVES - 1) * 12),velocity); octave_overflow = 0;}
    //if(which_note > 0) {noteOff(channel,ARPEGGIO[which_note - 1] + (which_octave * 12),velocity);}
    
    // !!! UP ARPEGGIO !!!
    if(ARPEGGIO_TYPE == UP | ARPEGGIO_TYPE == UP_DOWN | ARPEGGIO_TYPE == AS_PRESSED) {

        if(startingDirection == UP){
        //for UP/DOWN
            if((overflow == 1) && (which_octave > 0) && (octave_overflow == 0) && (flag1 == 0)){
                
                //*NOTE OFF 1* -- NOTE OFF AT END OF ARPEGGIO
                noteOff(channel,*(arpeggioPtr + (NUM_NOTES_PRESSED - 1)) + ((which_octave - 1) * 12),velocity);
                overflow = 0;
            }
        }
        
        if(startingDirection == DOWN){
        //for DOWN/UP
            if((overflow == 1) && (which_octave > 0) && (octave_overflow == 0) && (flag1 == 0)){
                noteOff(channel,*(arpeggioPtr + (NUM_NOTES_PRESSED - 1)) + ((which_octave - OCTAVES) * 12),velocity);
                overflow = 0;
            }
        }
        
        if(octave_overflow == 1){
            if(startingDirection == UP) {
                //for UP/DOWN
                if(flag2 == 0) {noteOff(channel,*(arpeggioPtr + (NUM_NOTES_PRESSED - 1)) + ((OCTAVES - 1) * 12),velocity);}
                octave_overflow = 0;
            }
            
            if(startingDirection == DOWN){
                //for DOWN/UP
                if(flag2 == 0) {noteOff(channel,*(arpeggioPtr + (NUM_NOTES_PRESSED - 1)),velocity);}
                octave_overflow = 0;
            }
            
            // TO NOT REPEAT FIRST/LAST NOTE OF ARPEGGIO
            //*** skipFirstLast here ***
            if(skipFirstLast == 1){
                if(NUM_NOTES_PRESSED > 1){
                    which_note = 1;
                    suppress_note_off = 1;
                }

                //KEYBOARD MODE individual note presses only!
                //if((NUM_NOTES_PRESSED) == 1 && (OCTAVES > 1)){
                if((NUM_NOTES_PRESSED == 1) && (OCTAVES > 1)){
                    flag1 = 1;
                    //flag2 = 1;
                    which_note = 0;
                    which_octave--;
                    stored_octave = which_octave;
                }
            }
            
            //reverse arpeggio 
            if(ARPEGGIO_TYPE == UP_DOWN) {ARPEGGIO_TYPE = DOWN_UP;}
        }
    }
    
    // !!! DOWN ARPEGGIO !!! (OCTAVES * -1) + 1
    if(ARPEGGIO_TYPE == DOWN | ARPEGGIO_TYPE == DOWN_UP) {

        if(startingDirection == UP){
            //for UP/DOWN
            if((overflow == 1) && (which_octave < 0) && (octave_overflow == 0) && (flag1 == 0)){
                noteOff(channel,*(arpeggioPtr + (NUM_NOTES_PRESSED - 1)) + ((OCTAVES + which_octave) * 12),velocity);
                overflow = 0;
            }
        }
        
        if(startingDirection == DOWN) {
            //for DOWN/UP
            if((overflow == 1) && (which_octave < 0) && (octave_overflow == 0) && (flag1 == 0)){
                noteOff(channel,*(arpeggioPtr + (NUM_NOTES_PRESSED - 1)) + ((which_octave + 1) * 12),velocity);
                overflow = 0;
            }
        }

        if(octave_overflow == 1){
            
            if(startingDirection == UP){
                //for UP/DOWN
                if(flag2 == 0) {noteOff(channel,*(arpeggioPtr + (NUM_NOTES_PRESSED - 1)) + (((OCTAVES * - 1) + OCTAVES) * 12),velocity);}
                octave_overflow = 0;
            }
            
            if(startingDirection == DOWN){
                //for DOWN/UP
                if(flag2 == 0) {noteOff(channel,*(arpeggioPtr + (NUM_NOTES_PRESSED - 1)) + (((OCTAVES * - 1) + 1) * 12),velocity);}
                octave_overflow = 0;
            }
            
            // TO NOT REPEAT LAST NOTE OF ARPEGGIO
            //*** skipFirstLast here ***
            if(skipFirstLast == 1){
                if(NUM_NOTES_PRESSED > 1){
                    which_note = 1;
                    suppress_note_off = 1;
                }

                //KEYBOARD MODE individual note presses only!
                //if((NUM_NOTES_PRESSED) == 1 && (OCTAVES > 1)){
                if((NUM_NOTES_PRESSED == 1) && (OCTAVES > 1)){                    
                    flag1 = 1;
                    //flag2 = 1;
                    which_note = 0;
                    which_octave++;
                    stored_octave = which_octave;
                }
            }
            
            if(ARPEGGIO_TYPE == DOWN_UP) {ARPEGGIO_TYPE = UP_DOWN;}
        }
    }
    
    //random arpeggio
    if(ARPEGGIO_TYPE == RANDOM | ARPEGGIO_TYPE == RANDOM_NON_REPEATING){
        
        last_octave = which_octave;  
                
        if((overflow == 1) && (flag1 == 0)){
            noteOff(channel,last_note + (last_octave * 12),velocity);
            overflow = 0;
        }           
        
        if((which_note > 0) && (suppress_note_off == 0)){noteOff(channel,*(arpeggioPtr + (which_note - 1)) + (which_octave * 12),velocity);}
        which_octave = rand() % OCTAVES; 
        if(suppress_note_on == 0){noteOn(channel,*(arpeggioPtr + which_note) + (which_octave * 12),velocity);}
    }
    
    if((ARPEGGIO_TYPE == UP) | (ARPEGGIO_TYPE == UP_DOWN | ARPEGGIO_TYPE == AS_PRESSED)) {
        
        SORT_DIRECTION = ASCENDING;
        sort_pitches();
        
        if(startingDirection == UP){
            //for UP/DOWN
            if((which_note > 0) && (suppress_note_off == 0)) {noteOff(channel,*(arpeggioPtr + (which_note - 1)) + (which_octave * 12),velocity);}
            if(suppress_note_on == 0){noteOn(channel,*(arpeggioPtr + which_note) + (which_octave * 12),velocity);}
        }
        
        if(startingDirection == DOWN) {
            //for DOWN/UP
            if((which_note > 0) && (suppress_note_off == 0)) {noteOff(channel,*(arpeggioPtr + (which_note - 1)) + ((which_octave - (OCTAVES - 1)) * 12),velocity);}    
            if(suppress_note_on == 0){noteOn(channel,*(arpeggioPtr + which_note) + ((which_octave - (OCTAVES - 1)) * 12),velocity);}
        }
    }
    
    if((ARPEGGIO_TYPE == DOWN) | (ARPEGGIO_TYPE == DOWN_UP)) {
        
        SORT_DIRECTION = DESCENDING;
        sort_pitches();

        suppress_note_on = 0;
        
        if(startingDirection == UP){
            //for UP/DOWN
            if((which_note > 0) && (suppress_note_off == 0)) {noteOff(channel,*(arpeggioPtr + (which_note - 1)) + ((which_octave + (OCTAVES - 1)) * 12),velocity);}    
            if(suppress_note_on == 0){noteOn(channel,*(arpeggioPtr + which_note) + ((which_octave + (OCTAVES - 1)) * 12),velocity);}
        }
        
        if(startingDirection == DOWN){
            //for DOWN/UP
            if((which_note > 0) && (suppress_note_off == 0)) {noteOff(channel,*(arpeggioPtr + (which_note - 1)) + ((which_octave) * 12),velocity);}    
            if(suppress_note_on == 0){noteOn(channel,*(arpeggioPtr + which_note) + (which_octave * 12),velocity);}
        }
    }
    
    last_note = *(arpeggioPtr + which_note);
    which_note++;
    suppress_note_off = 0;
    
    // ARPEGGIO_TYPE
    
    // UP
    // DOWN
    // UP/DOWN
    // DOWN/UP
    // RANDOM 1
    // RANDOM 2
    // AS PRESSED

    if((ARPEGGIO_TYPE == UP) | (ARPEGGIO_TYPE == UP_DOWN) | (ARPEGGIO_TYPE == RANDOM) | (ARPEGGIO_TYPE == RANDOM_NON_REPEATING) | ARPEGGIO_TYPE == AS_PRESSED) {
        
        if(which_note >= (NUM_NOTES_PRESSED)){
 
            which_note = 0;
            
            //only increment which_octave for UP/UP_DOWN arpeggio
            if((ARPEGGIO_TYPE == UP) | (ARPEGGIO_TYPE == UP_DOWN) | ARPEGGIO_TYPE == AS_PRESSED) {
                which_octave++;
            }
        
            overflow = 1;
            flag1 = 0;

            // !!! AUTO_RANDOMIZE here !!!
            if(ARPEGGIO_TYPE == RANDOM) {
                if(AUTO_RANDOMIZE == AUTOMATICALLY) {random_pitches();}
            }
            if(ARPEGGIO_TYPE == RANDOM_NON_REPEATING) {
                if(AUTO_RANDOMIZE == AUTOMATICALLY) {random_pitches_non_repeating();}
            }
        }
        
        if(which_octave>=OCTAVES) {
            which_octave = 0;
            octave_overflow = 1;
            flag2 = 0;
        }
    }
    
    //only decrement which_octave for DOWN/DOWN_UP arpeggio
    if((ARPEGGIO_TYPE == DOWN) | (ARPEGGIO_TYPE == DOWN_UP)) {
        
        if(which_note>=(NUM_NOTES_PRESSED)){
            which_note = 0;
            which_octave--;
            overflow = 1;
            flag1 = 0;
        }
        if(which_octave <= (OCTAVES * -1)) {
            which_octave = 0;
            octave_overflow = 1;
            flag2 = 0;
        }
    }
}

//get array index of key that was released
signed char findArrayIndex(unsigned char pitch_of_key_release){ //changed to signed char!
    //for (unsigned char i=0;i<NUM_NOTES_PRESSED;i++){
    for (unsigned char i=0;i<MAX_NUM_NOTES;i++){  
        if(ARPEGGIO[i] == pitch_of_key_release){return i;}
        else{;} //added this!
    }
}


// shift the array left at index calculated in 'findArrayIndex()'
// this code only works for MAX_NUM_NOTES of '8' !!!
void shiftTheArray(unsigned char array_index){

    //if array_index = 0, ARRAY[0] = ARRAY[1], ARRAY[1] = ARRAY[2], ARRAY[2] = ARRAY[3], ARRAY[3] = ARRAY[4], ARRAY[4] = ARRAY[5], ARRAY[5] = ARRAY[6], ARRAY[6] = ARRAY[7]
    //if array_index = 1, ARRAY[1] = ARRAY[2], ARRAY[2] = ARRAY[3], ARRAY[3] = ARRAY[4], ARRAY[4] = ARRAY[5], ARRAY[5] = ARRAY[6], ARRAY[6] = ARRAY[7]
    //if array_index = 2, ARRAY[2] = ARRAY[3], ARRAY[3] = ARRAY[4], ARRAY[4] = ARRAY[5], ARRAY[5] = ARRAY[6], ARRAY[6] = ARRAY[7]
    //if array_index = 3, ARRAY[3] = ARRAY[4], ARRAY[4] = ARRAY[5], ARRAY[5] = ARRAY[6], ARRAY[6] = ARRAY[7]
    //if array_index = 4, ARRAY[4] = ARRAY[5], ARRAY[5] = ARRAY[6], ARRAY[6] = ARRAY[7]
    //if array_index = 5, ARRAY[5] = ARRAY[6], ARRAY[6] = ARRAY[7]
    //if array_index = 6, ARRAY[6] = ARRAY[7]
    //if array_index = 7, nothing
    
    if (array_index == 0) {
        ARPEGGIO[0] = ARPEGGIO[1];
        ARPEGGIO[1] = ARPEGGIO[2];
        ARPEGGIO[2] = ARPEGGIO[3];
        ARPEGGIO[3] = ARPEGGIO[4];
        ARPEGGIO[4] = ARPEGGIO[5];
        ARPEGGIO[5] = ARPEGGIO[6];
        ARPEGGIO[6] = ARPEGGIO[7];
    }
    if (array_index == 1) {
        ARPEGGIO[1] = ARPEGGIO[2];
        ARPEGGIO[2] = ARPEGGIO[3];
        ARPEGGIO[3] = ARPEGGIO[4];
        ARPEGGIO[4] = ARPEGGIO[5];
        ARPEGGIO[5] = ARPEGGIO[6];
        ARPEGGIO[6] = ARPEGGIO[7];
    }
    if (array_index == 2) {
        ARPEGGIO[2] = ARPEGGIO[3];
        ARPEGGIO[3] = ARPEGGIO[4];
        ARPEGGIO[4] = ARPEGGIO[5];
        ARPEGGIO[5] = ARPEGGIO[6];
        ARPEGGIO[6] = ARPEGGIO[7];
    }
    if (array_index == 3) {
        ARPEGGIO[3] = ARPEGGIO[4];
        ARPEGGIO[4] = ARPEGGIO[5];
        ARPEGGIO[5] = ARPEGGIO[6];
        ARPEGGIO[6] = ARPEGGIO[7];        
    }
    if (array_index == 4) {
        ARPEGGIO[4] = ARPEGGIO[5];
        ARPEGGIO[5] = ARPEGGIO[6];
        ARPEGGIO[6] = ARPEGGIO[7];         
    }
    if (array_index == 5) {
        ARPEGGIO[5] = ARPEGGIO[6];
        ARPEGGIO[6] = ARPEGGIO[7];     
    }
    if (array_index == 6) {
        ARPEGGIO[6] = ARPEGGIO[7];       
    }
    //if array_index = 7, nothing
}


void rotateArrayLeft (unsigned char array_index){
    
    // ORIGINAL BLOCK OF CODE:
    /*
    static unsigned char temp = 0;
        
    //shifts array LEFT once
    temp = ARPEGGIO[0];
    for(unsigned char i=0;i<n-1;i++)
    {
        ARPEGGIO[i]=ARPEGGIO[i+1];
    }
    ARPEGGIO[n-1]=temp;
    */
    
    // MODIFIED BLOCK OF CODE:
    //shifts array LEFT once AT A STARTING INDEX!
    //for(unsigned char i=array_index; i < (NUM_NOTES_PRESSED) ;i++)
    
    //added this (rotate)
    //static unsigned char temp;
    //temp = ARPEGGIO[0];
    
    for(unsigned char i=array_index; i < (MAX_NUM_NOTES - 1) ;i++) //changed to -2!!!
    {
        ARPEGGIO[i]=ARPEGGIO[i+1];
    }
    
    //added this (rotate)
    //ARPEGGIO[MAX_NUM_NOTES - 1]=temp;
    
}