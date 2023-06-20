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

#ifndef EEPROM_H_INCLUDED
#define EEPROM_H_INCLUDED

#include <xc.h>
#include "theory.h"
#include "drum.h"
#include "octave.h"
#include "potentiometers.h"
#include "arpeggio.h"

//set Slot1 = Slot2 = Slot3 = Slot4 *once* (after programming)
void initializeSaveSlotsOnce(void);
//select save slot to load on boot-up
void selectSlotOnBoot (void);
//save settings to EEPROM
void saveToEEPROM(unsigned char slotNumber);
//load settings from EEPROM
void loadFromEEPROM(unsigned char slotNumber);

//enum for 4 save slots and a DEFAULT
enum EEPROM_SLOT {
    DEFAULT,    //use variables set at compile time
    SLOT1,      //eeprom slot1
    SLOT2,      //eeprom slot2
    SLOT3,      //eeprom slot3
    SLOT4       //eeprom slot4
};

#define FIRST_BOOT 0x24         //calls initializeSaveSlotsOnce() --> Slot1 = Slot2 = Slot3 = Slot4
#define FIRST_BOOT_DONE 0x48    //IC has been programmed and booted up at least once
#define save_slot_number_of_bytes 75 //maximum of 128 bytes!

#endif