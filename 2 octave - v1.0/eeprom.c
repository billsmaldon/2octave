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

#include "eeprom.h"

__EEPROM_DATA(0x00,0x24,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);

void initializeSaveSlotsOnce(void) {
    
    unsigned char initializeSlotsOnce = eeprom_read(0x01);
    
    if (initializeSlotsOnce == FIRST_BOOT) {
        saveToEEPROM(SLOT1);
        saveToEEPROM(SLOT2);
        saveToEEPROM(SLOT3);
        saveToEEPROM(SLOT4);
        eeprom_write (0x01, FIRST_BOOT_DONE);
    }
}

void selectSlotOnBoot (void) {
    
    unsigned char slot = eeprom_read(0);
    
    if (slot == DEFAULT){
        return;
    }
    
    else {
        loadFromEEPROM(slot);
    }
}

void loadFromEEPROM(unsigned char slotNumber) {
    
    unsigned int baseAddress = 0;
    
    //128 byte save slots, starting at 0x80
    if (slotNumber == SLOT1) {baseAddress = 128;}
    if (slotNumber == SLOT2) {baseAddress = 256;}
    if (slotNumber == SLOT3) {baseAddress = 384;}
    if (slotNumber == SLOT4) {baseAddress = 512;}
    
    //64 bytes, counting all BOOLS as BYTES
    unsigned char to_load[64];    
    
    //read from EEPROM
    for (unsigned int byte_count = 0;byte_count<64;byte_count++){
        to_load[byte_count] = eeprom_read(byte_count + baseAddress);
    }
    
    /************ load array to variables ***************/
    
    //keyboard settings
    KEYBOARD_MODE       = to_load[0];
    which_mode          = to_load[1];
    which_triad         = to_load[2];
    which_seventh       = to_load[3];
    
    //transpose settings
    TRANSPOSE_MODE      = to_load[4];    //BIT
    
    //drum settings
    DRUM_MODE           = to_load[5];         //BIT
    CONTROL_MODE        = to_load[6];      //BIT
        
    //DRUM_NOTE[8]
    DRUM_NOTE[0]        = to_load[7];
    DRUM_NOTE[1]        = to_load[8];
    DRUM_NOTE[2]        = to_load[9];
    DRUM_NOTE[3]        = to_load[10];
    DRUM_NOTE[4]        = to_load[11];
    DRUM_NOTE[5]        = to_load[12];
    DRUM_NOTE[6]        = to_load[13];
    DRUM_NOTE[7]        = to_load[14];

    //DRUM_CC[8]
    DRUM_CC[0]          = to_load[15];
    DRUM_CC[1]          = to_load[16];
    DRUM_CC[2]          = to_load[17];
    DRUM_CC[3]          = to_load[18];
    DRUM_CC[4]          = to_load[19];
    DRUM_CC[5]          = to_load[20];
    DRUM_CC[6]          = to_load[21];
    DRUM_CC[7]          = to_load[22];

    //potentiometer settings
    POT_MODE            = to_load[23]; //BIT
        
    //handles all pots, slidepots and joystick controller numbers
    inputPotsArray[0].controller_number                 = to_load[24];
    inputPotsArray[0].controller_number_two_byte        = to_load[25];
    
    inputPotsArray[1].controller_number                 = to_load[26];
    inputPotsArray[1].controller_number_two_byte        = to_load[27];
    
    inputPotsArray[2].controller_number                 = to_load[28];
    inputPotsArray[2].controller_number_two_byte        = to_load[29];
    
    inputPotsArray[3].controller_number                 = to_load[30];
    inputPotsArray[3].controller_number_two_byte        = to_load[31];
    
    inputPotsArray[4].controller_number                 = to_load[32];
    inputPotsArray[4].controller_number_two_byte        = to_load[33];
    
    inputPotsArray[5].controller_number                 = to_load[34];
    inputPotsArray[5].controller_number_two_byte        = to_load[35];
    
    inputPotsArray[6].controller_number                 = to_load[36];
    inputPotsArray[6].controller_number_two_byte        = to_load[37];
    
    //UNCOMMENT THESE FOR 16 POTENTIOMETERS
    
    inputPotsArray[7].controller_number                 = to_load[38];
    inputPotsArray[7].controller_number_two_byte        = to_load[39];
    
    inputPotsArray[8].controller_number                 = to_load[40];
    inputPotsArray[8].controller_number_two_byte        = to_load[41];
    
    inputPotsArray[9].controller_number                 = to_load[42];
    inputPotsArray[9].controller_number_two_byte        = to_load[43];
    
    inputPotsArray[10].controller_number                = to_load[44];
    inputPotsArray[10].controller_number_two_byte       = to_load[45];
    
    inputPotsArray[11].controller_number                = to_load[46];
    inputPotsArray[11].controller_number_two_byte       = to_load[47];
    
    inputPotsArray[12].controller_number                = to_load[48];
    inputPotsArray[12].controller_number_two_byte       = to_load[49];
    
    inputPotsArray[13].controller_number                = to_load[50];
    inputPotsArray[13].controller_number_two_byte       = to_load[51];
    
    inputPotsArray[14].controller_number                = to_load[52];
    inputPotsArray[14].controller_number_two_byte       = to_load[53];
    
    inputPotsArray[15].controller_number                = to_load[54];
    inputPotsArray[15].controller_number_two_byte       = to_load[55];
    
     
    //MIDI channel settings
    channel         = to_load[56];
    drumchannel     = to_load[57];
    
    //octave settings
    octave          = to_load[58];
    semitone        = to_load[59]; //this variable is a signed char! (fix)
    
    //program change settings
    patch_number    = to_load[60];
}

//function to read from eeprom and set all stored variables
void saveToEEPROM(unsigned char slotNumber) {

    unsigned int baseAddress = 0;
    
    //128 byte save slots, starting at 0x80
    if (slotNumber == SLOT1) {baseAddress = 128;}
    if (slotNumber == SLOT2) {baseAddress = 256;}
    if (slotNumber == SLOT3) {baseAddress = 384;}
    if (slotNumber == SLOT4) {baseAddress = 512;}
    
    //64 bytes, counting all BOOLS as BYTES
    unsigned char to_save[64];

    /************ save variables to array ***************/

    //keyboard settings
    to_save[0] = KEYBOARD_MODE;
    to_save[1] = which_mode;
    to_save[2] = which_triad;
    to_save[3] = which_seventh;
    
    //transpose settings
    to_save[4] = TRANSPOSE_MODE;    //BIT
    
    //drum settings
    to_save[5] = DRUM_MODE;         //BIT
    to_save[6] = CONTROL_MODE;      //BIT
        
    //DRUM_NOTE[8]
    to_save[7] = DRUM_NOTE[0];
    to_save[8] = DRUM_NOTE[1];
    to_save[9] = DRUM_NOTE[2];
    to_save[10] = DRUM_NOTE[3];
    to_save[11] = DRUM_NOTE[4];
    to_save[12] = DRUM_NOTE[5];
    to_save[13] = DRUM_NOTE[6];
    to_save[14] = DRUM_NOTE[7];

    //DRUM_CC[8]
    to_save[15] = DRUM_CC[0];
    to_save[16] = DRUM_CC[1];
    to_save[17] = DRUM_CC[2];
    to_save[18] = DRUM_CC[3];
    to_save[19] = DRUM_CC[4];
    to_save[20] = DRUM_CC[5];
    to_save[21] = DRUM_CC[6];
    to_save[22] = DRUM_CC[7];

    //potentiometer settings
    to_save[23] = POT_MODE; //BIT
        
    //handles all pots, slidepots and joystick controller numbers
    to_save[24] = inputPotsArray[0].controller_number;
    to_save[25] = inputPotsArray[0].controller_number_two_byte;
    
    to_save[26] = inputPotsArray[1].controller_number;
    to_save[27] = inputPotsArray[1].controller_number_two_byte;
    
    to_save[28] = inputPotsArray[2].controller_number;
    to_save[29] = inputPotsArray[2].controller_number_two_byte;
    
    to_save[30] = inputPotsArray[3].controller_number;
    to_save[31] = inputPotsArray[3].controller_number_two_byte;
    
    to_save[32] = inputPotsArray[4].controller_number;
    to_save[33] = inputPotsArray[4].controller_number_two_byte;
    
    to_save[34] = inputPotsArray[5].controller_number;
    to_save[35] = inputPotsArray[5].controller_number_two_byte;
    
    to_save[36] = inputPotsArray[6].controller_number;
    to_save[37] = inputPotsArray[6].controller_number_two_byte;
    
    //UNCOMMENT THESE FOR 16 POTENTIOMETERS
    
    to_save[38] = inputPotsArray[7].controller_number;
    to_save[39] = inputPotsArray[7].controller_number_two_byte;
    
    to_save[40] = inputPotsArray[8].controller_number;
    to_save[41] = inputPotsArray[8].controller_number_two_byte;
    
    to_save[42] = inputPotsArray[9].controller_number;
    to_save[43] = inputPotsArray[9].controller_number_two_byte;
    
    to_save[44] = inputPotsArray[10].controller_number;
    to_save[45] = inputPotsArray[10].controller_number_two_byte;
    
    to_save[46] = inputPotsArray[11].controller_number;
    to_save[47] = inputPotsArray[11].controller_number_two_byte;
    
    to_save[48] = inputPotsArray[12].controller_number;
    to_save[49] = inputPotsArray[12].controller_number_two_byte;
    
    to_save[50] = inputPotsArray[13].controller_number;
    to_save[51] = inputPotsArray[13].controller_number_two_byte;
    
    to_save[52] = inputPotsArray[14].controller_number;
    to_save[53] = inputPotsArray[14].controller_number_two_byte;
    
    to_save[54] = inputPotsArray[15].controller_number;
    to_save[55] = inputPotsArray[15].controller_number_two_byte;    
    
    
    //MIDI channel settings
    to_save[56] = channel;
    to_save[57] = drumchannel;
    
    //octave settings
    to_save[58] = octave;
    to_save[59] = semitone; //this variable is a signed char! (fix))
    
    //program change settings
    to_save[60] = patch_number;

    //unused bytes
    to_save[61] = 0xFF;
    to_save[62] = 0xFF;
    to_save[63] = 0xFF;
    
    //write to EEPROM
    for (unsigned int byte_count = 0;byte_count<64;byte_count++){
        eeprom_write((byte_count + baseAddress), to_save[byte_count]);
     }
}

