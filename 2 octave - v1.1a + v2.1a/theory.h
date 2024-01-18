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

#ifndef THEORY_H_INCLUDED
#define THEORY_H_INCLUDED

//enum music notes
enum musicNotes {
    //octave 1
	C,
	Cs,
	D,
	Ds,
	E,
	F,
	Fs,
	G,
	Gs,
	A,
	As,
	B,
    //octave 2
	C2,
	C2s,
	D2,
	D2s,
	E2,
	F2,
	F2s,
	G2,
	G2s,
	A2,
	A2s,
	B2,
    //octave 3
    C3
};

//pitch intervals
enum intervals {
    tonic            =  0,
    minor_second     =  1,
    major_second     =  2,
    minor_third      =  3,
    major_third      =  4,
    perfect_fourth   =  5,
    tri_tone         =  6,
    diminished_fifth =  6,
    perfect_fifth    =  7,
    augmented_fifth  =  8,
    minor_sixth      =  8,
    major_sixth      =  9,
    diminished_seventh = 9,
    minor_seventh    = 10,
    major_seventh    = 11,
    perfect_octave   = 12
};
//keyboard mode
enum keyboard_mode {
    CHROMATIC,
    MAJOR,
    MINOR,
    MODES,
    PENTATONIC_MAJOR,
    PENTATONIC_MINOR,
    TRIAD,
    DIATONIC_TRIAD_MAJOR,
    DIATONIC_TRIAD_MINOR,
    SEVENTH,
    DIATONIC_7TH_MAJOR,
    DIATONIC_7TH_MINOR,
};

//keyboard mode defaults to CHROMATIC
unsigned char KEYBOARD_MODE = CHROMATIC;

//tonic, half-step, whole step
#define T 0 //tonic
#define H 1 //half step
#define W 2 //whole step

//major and minor scales - by half-step, whole step (not used in code)
//unsigned char major_key[] = {T,W,W,H,W,W,W,H};
//unsigned char minor_key[] = {T,W,H,W,W,H,W,W};

//major and minor scales - integer notation (running sum of half-steps and whole steps)
const unsigned char major_key[] = {T,2,4,5,7,9,11,12,14,16,17,19,21,23,24};
const unsigned char minor_key[] = {T,2,3,5,7,8,10,12,14,15,17,19,20,22,24};

//pentatonic major and minor scales - by whole step, whole step + half step (not used in code)
//unsigned char pentatonic_major_key[] = {T,W,W,W+H,W,W+H};
//unsigned char pentatonic_minor_key[] = {T,W+H,W,W,W+H,W};

//major and minor pentatonic scales - integer notation (running sum of half-steps and whole steps)
const unsigned char pentatonic_major_key[] = {T,2,4,7,9,12,14,16,19,21,24};
const unsigned char pentatonic_minor_key[] = {T,3,5,7,10,12,15,17,19,22,24};

//modes - by half-step, whole step (not used in code)
//unsigned char ionian_key[]      =   {C,W,W,H,W,W,W,H}; 
//unsigned char dorian_key[]      =   {D,W,H,W,W,W,H,W};
//unsigned char phrygian_key[]    =   {E,H,W,W,W,H,W,W}; 
//unsigned char lydian_key[]      =   {F,W,W,W,H,W,W,H};
//unsigned char mixolydian_key[]  =   {G,W,W,H,W,W,H,W};
//unsigned char aeolian_key[]     =   {A,W,H,W,W,H,W,W}; 
//unsigned char locrian_key[]     =   {B,H,W,W,H,W,W,W};

//modes - integer notation (running sum of half-steps and whole steps)
const unsigned char ionian_key[]      =   {C,2,4,5,7,9,11,12,14,16,17,19,21,23,24}; 
const unsigned char dorian_key[]      =   {D,2,3,5,7,9,10,12,14,15,17,19,21,22,24};
const unsigned char phrygian_key[]    =   {E,1,3,5,7,8,10,12,13,15,17,19,20,22,24}; 
const unsigned char lydian_key[]      =   {F,2,4,6,7,9,11,12,14,16,18,19,21,23,24};
const unsigned char mixolydian_key[]  =   {G,2,4,5,7,9,10,12,14,16,17,19,21,22,24};
const unsigned char aeolian_key[]     =   {A,2,3,5,7,8,10,12,14,15,17,19,20,22,24}; 
const unsigned char locrian_key[]     =   {B,1,3,5,6,8,10,12,13,15,17,18,20,22,24};

//enum of modes
enum modes {
    ionian,
    dorian,
    phrygian,
    lydian,
    mixolydian,
    aeolian,
    locrian
};

//sets default mode to ionian
unsigned char which_mode = ionian;

//enum of triads
enum triads {
    major,
    minor,
    augmented,
    diminished
};

//sets default triad to major
unsigned char which_triad = major;

//triads - array initialized with enum of intervals
unsigned char major_triad[] = {tonic, major_third, perfect_fifth};
unsigned char minor_triad[] = {tonic, minor_third, perfect_fifth};
unsigned char augmented_triad[]  = {tonic, major_third, augmented_fifth};
unsigned char diminished_triad[] = {tonic, minor_third, diminished_fifth};

//enum of seventh chords
enum sevenths {
    dominant7,
    major7,
    minor7,
    half_diminished7,
    diminished7
};

//sets default 7th chord to dominant7
unsigned char which_seventh = dominant7;

//seventh chords - array initialized with enum of intervals
unsigned char dominant_7th[] = {tonic, major_third, perfect_fifth, minor_seventh};
unsigned char major_7th[] = {tonic, major_third, perfect_fifth, major_seventh};
unsigned char minor_7th[] = {tonic, minor_third, perfect_fifth, minor_seventh};
unsigned char half_diminished_7th[] = {tonic, minor_third, diminished_fifth, minor_seventh};
unsigned char diminished_7th[] = {tonic, minor_third, diminished_fifth, diminished_seventh};

//diatonic major triads - array initialized with enum of intervals
const unsigned char diatonic_major[15][3] = {
    //major_triad
    {tonic, major_third, perfect_fifth},
    //minor_triad
    {tonic, minor_third, perfect_fifth},
    //minor_triad
    {tonic, minor_third, perfect_fifth},
    //major_triad
    {tonic, major_third, perfect_fifth},
    //major_triad
    {tonic, major_third, perfect_fifth},
    //minor_triad
    {tonic, minor_third, perfect_fifth},
    //diminished_triad
    {tonic, minor_third, diminished_fifth},
    
    //paste here
    
    //major_triad - octave 2
    {tonic, major_third, perfect_fifth},
    //minor_triad
    {tonic, minor_third, perfect_fifth},
    //minor_triad
    {tonic, minor_third, perfect_fifth},
    //major_triad
    {tonic, major_third, perfect_fifth},
    //major_triad
    {tonic, major_third, perfect_fifth},
    //minor_triad
    {tonic, minor_third, perfect_fifth},
    //diminished_triad
    {tonic, minor_third, diminished_fifth},
    
    //end of paste
    
    //major_triad - octave 3 (KEY C3)
    {tonic, major_third, perfect_fifth}
    
};

//diatonic minor triads - array initialized with enum of intervals
const unsigned char diatonic_minor[15][3] = {
    //minor_triad
    {tonic, minor_third, perfect_fifth},
    //diminished_triad
    {2, minor_third, diminished_fifth},
    //major_triad
    {3, major_third, perfect_fifth},
    //minor_triad
    {5, minor_third, perfect_fifth},
    //minor_triad
    {7, minor_third, perfect_fifth},
    //major_triad
    {8, major_third, perfect_fifth},
    //major_triad
    {10, major_third, perfect_fifth},
    
    //paste here
    
    //minor_triad - octave 2
    {tonic + 12, minor_third, perfect_fifth},
    //diminished_triad
    {2 + 12, minor_third, diminished_fifth},
    //major_triad
    {3 + 12, major_third, perfect_fifth},
    //minor_triad
    {5 + 12, minor_third, perfect_fifth},
    //minor_triad
    {7 + 12, minor_third, perfect_fifth},
    //major_triad
    {8 + 12, major_third, perfect_fifth},
    //major_triad
    {10 + 12, major_third, perfect_fifth},
    
    //end of paste
    
    //minor_triad - KEY C3
    {tonic + 24, minor_third, perfect_fifth}
};

//diatonic seventh major chords - array initialized with enum of intervals
const unsigned char diatonic_seventh_major[15][4] = {
    //major 7th
    {tonic, major_third, perfect_fifth, major_seventh},
    //minor 7th
    {tonic, minor_third, perfect_fifth, minor_seventh},
    //minor 7th
    {tonic, minor_third, perfect_fifth, minor_seventh},
    //major 7th
    {tonic, major_third, perfect_fifth, major_seventh},
    //dominant 7th
    {tonic, major_third, perfect_fifth, minor_seventh},
    //minor 7th
    {tonic, minor_third, perfect_fifth, minor_seventh},
    //half diminished 7th
    {tonic, minor_third, diminished_fifth, minor_seventh},
    
    //paste here

    //major 7th - octave 2
    {tonic, major_third, perfect_fifth, major_seventh},
    //minor 7th
    {tonic, minor_third, perfect_fifth, minor_seventh},
    //minor 7th
    {tonic, minor_third, perfect_fifth, minor_seventh},
    //major 7th
    {tonic, major_third, perfect_fifth, major_seventh},
    //dominant 7th
    {tonic, major_third, perfect_fifth, minor_seventh},
    //minor 7th
    {tonic, minor_third, perfect_fifth, minor_seventh},
    //half diminished 7th
    {tonic, minor_third, diminished_fifth, minor_seventh},    
    
    
    //end of paste
    
    //major 7th - KEY C3
    {tonic, major_third, perfect_fifth, major_seventh}  

};

//diatonic seventh minor chords - array initialized with enum of intervals
const unsigned char diatonic_seventh_minor[15][4] = {
    //minor 7th
    {tonic, minor_third, perfect_fifth, minor_seventh},
    //half diminished 7th
    {2, minor_third, diminished_fifth, minor_seventh},
    //major 7th
    {3, major_third, perfect_fifth, major_seventh},
    //minor 7th
    {5, minor_third, perfect_fifth, minor_seventh},
    //minor 7th
    {7, minor_third, perfect_fifth, minor_seventh},
    //major 7th
    {8, major_third, perfect_fifth, major_seventh},
    //dominant 7th
    {10, major_third, perfect_fifth, minor_seventh},
    
    //paste here
    
    //minor 7th - octave 2
    {tonic + 12, minor_third, perfect_fifth, minor_seventh},
    //half diminished 7th
    {2 + 12, minor_third, diminished_fifth, minor_seventh},
    //major 7th
    {3 + 12, major_third, perfect_fifth, major_seventh},
    //minor 7th
    {5 + 12, minor_third, perfect_fifth, minor_seventh},
    //minor 7th
    {7 + 12, minor_third, perfect_fifth, minor_seventh},
    //major 7th
    {8 + 12, major_third, perfect_fifth, major_seventh},
    //dominant 7th
    {10 + 12, major_third, perfect_fifth, minor_seventh},    
        
    //end of paste

    //minor 7th - KEY C3
    {tonic + 24, minor_third, perfect_fifth, minor_seventh}
    
};

#endif