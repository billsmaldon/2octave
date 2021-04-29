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

#include "menu.h"
#include "ascii.h"
#include "theory.h"
#include "octave.h"
#include "drum.h"
#include "eeprom.h"

//fills in addresses of display strings
void initializeMenuArray(void) {
 
    //calculate number of menu items
    unsigned char NumberOfElements = sizeof(menuArray)/sizeof(menuArray[0]);
    
    //calculate addresses of menu items
    for(unsigned char i = 1;i<NumberOfElements;i++) {
        menuArray[i].address = menuArray[i-1].address + menuArray[i-1].number;
    }

    //initialize the individual "menu_type" variables from menuArray[]
    mainMenu = menuArray[0];
    keyboardMenu = menuArray[1];
    modeMenu = menuArray[2];
    triadMenu = menuArray[3];
    seventhMenu = menuArray[4];
    transposeMenu = menuArray[5];
    drumMenu = menuArray[6];
    drumCCTypeMenu = menuArray[7];
    drumNNMenu = menuArray[8];    
    drumCCMenu = menuArray[9];
    potsMenu = menuArray[10];
    potsResoMenu = menuArray[11];
    potsCCMenu = menuArray[12];
    slidepotsCCMenu = menuArray[13];
    joystickCCMenu = menuArray[14];    
    midiChannelMenu = menuArray[15];
    eepromMenu = menuArray[16];
    savesMenu = menuArray[17];
}

//clears row 1 of LCD and sets cursor to 1,1
void clear_row1(void) {
    Lcd_Set_Cursor(1,1);
    Lcd_Print_String("                ");
    Lcd_Set_Cursor(1,1);
}

//clears row 2 of LCD and sets cursor to 2,1
void clear_row2(void) {
    Lcd_Set_Cursor(2,1);
    Lcd_Print_String("                ");
    Lcd_Set_Cursor(2,1);
}

//converts a signed char to a string
void int2string(signed char number) {
    
    static __bit isNegative = 0;            
    signed int number_to_display_temp = 0; 
    
    if(number < 0) {        //is number to display negative?
        isNegative = 1;     //set flag bit
        number_to_display_temp = (0 - number);  //convert negative number to positive number
    }
    else {
        isNegative = 0;     //clear flag bit
        number_to_display_temp = number;
    }
    
    //uses string2display[0] for minus sign or prints a space
    if(isNegative) {
        string2display[0] = '-';        //set left most char to '-' sign
    }
    else{string2display[0] = ' ';}      //left most char is ' '
    
    //string2display[0] = 48 + ((number_to_display_temp / 1000) % 10); //thou 10^3
    string2display[1] = 48 + ((number_to_display_temp / 100) % 10);    //hund 10^2
    string2display[2] = 48 + ((number_to_display_temp / 10) % 10);     //tens 10^1
    string2display[3] = 48 +  (number_to_display_temp % 10);           //ones 10^0
    string2display[4] = '\0';                                          //NULL
  
}

//sets resolution of ALL continuous controllers
void setControllerResolution(void){
    
    for(unsigned char i=0;i<NUM_ANALOG;i++){
        //set controller resolutions to all 0 or all 1
        inputPotsArray[i].controller_resolution = POT_MODE;
    }
    
}

//sets controller numbers
void setControllerNumbers(unsigned char array_index){
    
    which_screen = BLANK;
    lcd_print_once = 0; 
    encoder_click = 0;
    
    while(encoder_click == 0) {

    //two ranges for LO_RES/HI_RES controller numbers
    // 64-119 LO_RES, 0-31 HI_RES
        
    if(lcd_print_once == 0) {
            
        if (encoder_direction == DIR_CW) {
                
            if(inputPotsArray[array_index].controller_resolution == LO_RES){
                if(inputPotsArray[array_index].controller_number < 119) {
                    inputPotsArray[array_index].controller_number++;
                    if(inputPotsArray[array_index].controller_number == 0){inputPotsArray[array_index].controller_number = 64;}
                }
            }
                
            if(inputPotsArray[array_index].controller_resolution == HI_RES){
                if(inputPotsArray[array_index].controller_number_two_byte < 31) {
                    inputPotsArray[array_index].controller_number_two_byte++;
                }
            }
                
            encoder_direction = DIR_NONE;
        }
            
            
        //make CC#-1 set velocity, CC#-2 pitch bend, CC#-3 modulation wheel
        if (encoder_direction == DIR_CCW) {
                
            if(inputPotsArray[array_index].controller_resolution == LO_RES){
                    
                if(inputPotsArray[array_index].controller_number > -3) {
                    inputPotsArray[array_index].controller_number--;
                }
                if(inputPotsArray[array_index].controller_number == 61) {inputPotsArray[array_index].controller_number = -3;}                    
                if(inputPotsArray[array_index].controller_number == 62) {inputPotsArray[array_index].controller_number = -2;}
                if(inputPotsArray[array_index].controller_number == 63) {inputPotsArray[array_index].controller_number = -1;}

            }
                
            if(inputPotsArray[array_index].controller_resolution == HI_RES){
                    
                if(inputPotsArray[array_index].controller_number_two_byte > -3) {
                    inputPotsArray[array_index].controller_number_two_byte--;
                }
                    
            }
                
            encoder_direction = DIR_NONE;
        }

        if(inputPotsArray[array_index].controller_resolution == LO_RES){
            
            if(inputPotsArray[array_index].controller_number >= 0) {
                    
                int2string(inputPotsArray[array_index].controller_number);
                
                Lcd_Set_Cursor(2,7);
                Lcd_Print_String("         ");
                Lcd_Set_Cursor(2,13);
                Lcd_Print_String(string2display);
            }
            else {
                if(inputPotsArray[array_index].controller_number == -1) {
                    Lcd_Set_Cursor(2,7);
                    Lcd_Print_String("  VELOCITY");
                }
            
                if(inputPotsArray[array_index].controller_number == -2) {
                    Lcd_Set_Cursor(2,7);
                    Lcd_Print_String(" PITCHBEND");
                }
                if(inputPotsArray[array_index].controller_number == -3) {
                    Lcd_Set_Cursor(2,7);
                    Lcd_Print_String(" MOD.WHEEL");
                }                    
            }
        }                
    }
            
        if(inputPotsArray[array_index].controller_resolution == HI_RES){
            
            if(inputPotsArray[array_index].controller_number_two_byte >= 0) {
                    
                int2string(inputPotsArray[array_index].controller_number_two_byte);
                
                Lcd_Set_Cursor(2,7);
                Lcd_Print_String("         ");
                Lcd_Set_Cursor(2,13);
                Lcd_Print_String(string2display);
            }
            else {
                if(inputPotsArray[array_index].controller_number_two_byte == -1) {
                    Lcd_Set_Cursor(2,7);
                    Lcd_Print_String("  VELOCITY");
                }
         
                if(inputPotsArray[array_index].controller_number_two_byte == -2) {
                    Lcd_Set_Cursor(2,7);
                    Lcd_Print_String(" PITCHBEND");
                }
                if(inputPotsArray[array_index].controller_number_two_byte == -3) {
                    Lcd_Set_Cursor(2,7);
                    Lcd_Print_String(" MOD.WHEEL");
                }                    
            }
        }
    }
}

//exits most functions
void exitFunction(void) {
    
    while(encoder_click == 0); //wait for encoder click
    clear_row1();
    Lcd_Print_String("Set!");   //exit function 
    __delay_ms(500);            //hold on this screen for 1/2 second
    which_screen = MAIN_MENU;   //use timer interrupt    
    lcd_print_once = 0;
    encoder_click = 0;
    
}

//exits save function
void exitSave(void) {
    
    while(encoder_click == 0); //wait for encoder click
    clear_row1();
    Lcd_Print_String("Settings Saved!");   //exit function 
    __delay_ms(500);            //hold on this screen for 1/2 second
    which_screen = MAIN_MENU;   //use timer interrupt    
    lcd_print_once = 0;
    encoder_click = 0;
    
}

//exits load function
void exitLoad(void) {
    
    while(encoder_click == 0); //wait for encoder click
    clear_row1();
    Lcd_Print_String("Settings Loaded!");   //exit function 
    __delay_ms(500);            //hold on this screen for 1/2 second
    which_screen = MAIN_MENU;   //use timer interrupt    
    lcd_print_once = 0;
    encoder_click = 0;
    
}

//exits eeprom function
void eepromExit(void) {
    
    while(encoder_click == 0); //wait for encoder click
    clear_row1();
    Lcd_Print_String("Exit EEPROM!");   //exit function 
    __delay_ms(500);            //hold on this screen for 1/2 second
    which_screen = MAIN_MENU;   //use timer interrupt    
    lcd_print_once = 0;
    encoder_click = 0;
    
}

// !!! main menu function !!!
void menu_lcd(void) {
    
    which_screen = MAIN_MENU;
    
    //print main menu on LCD
    if (lcd_print_once == 0) {
        
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        
        //mainMenu.address
        //mainMenu.number
        //mainMenu.selector
        
        Lcd_Print_String(LCD_STRINGS[(mainMenu.selector % mainMenu.number) + mainMenu.address]);

        lcd_print_once = 1;
    }
    
    if(encoder_click == 1) {

        encoder_click = 0;
    
      
        switch (mainMenu.selector) {
            case 0:
                Function_A();
                exitFunction();
                break;
            case 1:
                Function_B();
                exitFunction();
                break;
            case 2:
                Function_C();
                exitFunction();
                break;
            case 3:
                Function_D();
                exitFunction();
                break;
            case 4:
                Function_E();
                exitFunction();
                break;
            case 5:
                Function_F();
                exitFunction();
                break;
            case 6:
                Function_G();
                //exitFunction();
            default:
                break;
        }
    }
}

//set MODES
void Function_A_1(void){
    
    KEYBOARD_MODE = MODES;
    which_screen = MODES_MENU;
    encoder_click = 0;
        
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String("Enter Mode:"); //keyboard menu
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(modeMenu.selector % modeMenu.number) + modeMenu.address]); //modes menu
        }
        which_mode = modeMenu.selector % modeMenu.number;
        lcd_print_once = 1;
    }
}

//set TRIADS
void Function_A_2(void){
    KEYBOARD_MODE = TRIAD;
    which_screen = TRIADS_MENU;
    encoder_click = 0;
        
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String("Select Triad:"); //keyboard menu
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(triadMenu.selector % triadMenu.number) + triadMenu.address]); //modes menu
        }
        which_triad = triadMenu.selector % triadMenu.number;
        lcd_print_once = 1;
    }
}

//set SEVENTHS
void Function_A_3(void){
    KEYBOARD_MODE = SEVENTH;
    which_screen = SEVENTHS_MENU;
    encoder_click = 0;
        
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String("Select Seventh:"); //keyboard menu
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(seventhMenu.selector % seventhMenu.number) + seventhMenu.address]); //modes menu
        }
        which_seventh = seventhMenu.selector % seventhMenu.number;
        lcd_print_once = 1;
    }
}

//KEYBOARD MODE MENU
void Function_A(void) {
    
    //keyboardMenu
    
    which_screen = KEYBOARD_MENU;
    lcd_print_once = 0;    
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(keyboardMenu.selector % keyboardMenu.number) + keyboardMenu.address]); //keyboard menu
            KEYBOARD_MODE = keyboardMenu.selector;
        }
        lcd_print_once = 1;
    }
    
    lcd_print_once = 0;
    
    // sub-menu "MODES"
    if(keyboardMenu.selector == MODES) {
        Function_A_1();
    }    
    
    // sub-menu "TRIAD"
    if(keyboardMenu.selector == TRIAD) {
        Function_A_2();
        
    }
    // sub-menu "SEVENTH"
    if(keyboardMenu.selector == SEVENTH){
        Function_A_3();
    }
    

        
}

//set TRANSPOSE MODE
void Function_B(void) {
    
    which_screen = TRANSPOSE_MENU;
    lcd_print_once = 0;    
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(transposeMenu.selector % transposeMenu.number) + transposeMenu.address]); //transpose menu
            TRANSPOSE_MODE = transposeMenu.selector % transposeMenu.number;
        }
        lcd_print_once = 1;
    }    
}

//set DRUMS CC TYPE
void Function_C_1(void){

    which_screen = DRUMS_CC_TYPE_MENU;
    lcd_print_once = 0; 
    encoder_click = 0;
        
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String("Drum CC Mode:"); //keyboard menu
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(drumCCTypeMenu.selector % drumCCTypeMenu.number) + drumCCTypeMenu.address]); //modes menu
        }
        lcd_print_once = 1;
    }    
    
    CONTROL_MODE = drumCCTypeMenu.selector % drumCCTypeMenu.number;
}

//set DRUMS NOTE NUMBER
void Function_C_2(void){
    
    //array_index = 0;
    //do something here
    which_screen = DRUMS_NN_MENU;
    lcd_print_once = 0; 
    encoder_click = 0;
        
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String("Set Note Number:"); //keyboard menu
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(drumNNMenu.selector % drumNNMenu.number) + drumNNMenu.address]); //modes menu
        }
        lcd_print_once = 1;
    }
    
    which_screen = BLANK;
    lcd_print_once = 0; 
    encoder_click = 0;
    unsigned char array_index = drumNNMenu.selector;

    while(encoder_click == 0) {

        if(lcd_print_once == 0) {
            if (encoder_direction == DIR_CW) {
                if(DRUM_NOTE[array_index] < 81) {
                    DRUM_NOTE[array_index]++;
                }
                encoder_direction = DIR_NONE;
            }
            //drum note--
            if (encoder_direction == DIR_CCW) {
                if(DRUM_NOTE[array_index] > 35) {
                    DRUM_NOTE[array_index]--;
                }
                encoder_direction = DIR_NONE;
            }
            
            int2string(DRUM_NOTE[array_index]);
            Lcd_Set_Cursor(2,13);
            Lcd_Print_String(string2display);
        }    
    }

}

//set DRUMS CC NUMBER
void Function_C_3(void){

    which_screen = DRUMS_CC_MENU;
    lcd_print_once = 0; 
    encoder_click = 0;
        
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String("Set CC Number:"); //keyboard menu
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(drumCCMenu.selector % drumCCMenu.number) + drumCCMenu.address]); //modes menu
        }
        lcd_print_once = 1;
    }    

    which_screen = BLANK;
    lcd_print_once = 0; 
    encoder_click = 0;
    unsigned char array_index = drumCCMenu.selector;

    while(encoder_click == 0) {

        if(lcd_print_once == 0) {
            if (encoder_direction == DIR_CW) {
                if(DRUM_CC[array_index] < 127) {
                    DRUM_CC[array_index]++;
                }
                encoder_direction = DIR_NONE;
            }
            //drum note--
            if (encoder_direction == DIR_CCW) {
                if(DRUM_CC[array_index] > 0) {
                    DRUM_CC[array_index]--;
                }
                encoder_direction = DIR_NONE;
            }
            
            int2string(DRUM_CC[array_index]);
            Lcd_Set_Cursor(2,13);
            Lcd_Print_String(string2display);
        }    
    }    
}

//DRUM MENU
void Function_C(void) {

    which_screen = DRUM_MENU;
    lcd_print_once = 0;    
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(drumMenu.selector % drumMenu.number) + drumMenu.address]); //transpose menu
            //cut and paste here
        }
        lcd_print_once = 1;
    }
    
    if(drumMenu.selector == NOTE){DRUM_MODE = NOTE;}
    if(drumMenu.selector == CONTROL){DRUM_MODE = CONTROL;}
    if(drumMenu.selector == 2) {Function_C_1();}  
    if(drumMenu.selector == 3) {Function_C_2();}
    if(drumMenu.selector == 4) {Function_C_3();}    
}

//set POTENTIOMETER RESOLUTION
void Function_D_1(void){
    
    which_screen = POTS_RES_MENU;
    lcd_print_once = 0;
    encoder_click = 0;
    
    potsResoMenu.selector = POT_MODE;
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String("Pots Resolution:"); //keyboard menu            
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(potsResoMenu.selector % potsResoMenu.number) + potsResoMenu.address]); //transpose menu
        }
        lcd_print_once = 1;
    }

    // !!! IMPORTANT !!!
    // set potentiometer resolution = potsResoMenu.selector
    // call function to set/clear inputPotsArray[].resolution
    
    POT_MODE = potsResoMenu.selector;
    setControllerResolution();

}

//set POTENTIOMETER CC NUMBER
void Function_D_2(void){
    //do something here
    
    //do something here
    which_screen = POTS_CC_MENU;
    
    lcd_print_once = 0; 
    encoder_click = 0;
        
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String("Set Pots CC#:"); //keyboard menu
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(potsCCMenu.selector % potsCCMenu.number) + potsCCMenu.address]); //modes menu
        }
        lcd_print_once = 1;
    }    
    
    unsigned char array_index = potsCCMenu.selector;
    setControllerNumbers(array_index);
 
}

//set SLIDEPOTS CC NUMBER
void Function_D_3(void){
    
    which_screen = SLIDEPOTS_CC_MENU;
    
    lcd_print_once = 0; 
    encoder_click = 0;
        
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String("Slidepots CC#:"); //keyboard menu
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(slidepotsCCMenu.selector % slidepotsCCMenu.number) + slidepotsCCMenu.address]); //modes menu
        }
        lcd_print_once = 1;
    }    
    
    //unsigned char array_index = slidepotsCCMenu.selector;
    //unsigned char array_index = 4; // COMMENTED THIS OUT!!!
    
    unsigned char array_index = (slidepotsCCMenu.selector) + 7;
    setControllerNumbers(array_index);

}

//set JOYSTICK CC NUMBER
void Function_D_4(void){
    
    which_screen = JOYSTICK_CC_MENU;
    
    lcd_print_once = 0; 
    encoder_click = 0;
        
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String("Set Joystick CC#"); //keyboard menu
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(joystickCCMenu.selector % joystickCCMenu.number) + joystickCCMenu.address]); //modes menu
        }
        lcd_print_once = 1;
    }    
    
    //unsigned char array_index = joystickCCMenu.selector + 5; //COMMENTED THIS OUT!!
    
    unsigned char array_index = (joystickCCMenu.selector) + 14;
    setControllerNumbers(array_index);
    
}

//POTENTIOMETER MENU
void Function_D(void) {
    
    which_screen = POTENTIOMETER_MENU;
    lcd_print_once = 0;    
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(potsMenu.selector % potsMenu.number) + potsMenu.address]); //transpose menu
        }
        lcd_print_once = 1;
    }

    if(potsMenu.selector == 0) {Function_D_1();}
    if(potsMenu.selector == 1) {Function_D_2();}
    if(potsMenu.selector == 2) {Function_D_3();}
    if(potsMenu.selector == 3) {Function_D_4();}
    
}

//set MAIN CHANNEL
void Function_E_1(void){

    which_screen = MAIN_CH_MENU;
    lcd_print_once = 0;
    encoder_click = 0;
    mainChannelMenu.selector = channel;
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        lcd_print_once = 1;
        //lcd print midi channel
        int2string((mainChannelMenu.selector) + 1);
        //int2string(channel + 1);
        Lcd_Set_Cursor(2,13);
        Lcd_Print_String(string2display);
    }
    
    channel = mainChannelMenu.selector;
}

//set DRUM CHANNEL
void Function_E_2(void){

    which_screen = DRUM_CH_MENU;
    lcd_print_once = 0;
    encoder_click = 0;
    drumChannelMenu.selector = drumchannel;
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        lcd_print_once = 1;
        int2string((drumChannelMenu.selector) + 1);
        Lcd_Set_Cursor(2,13);
        Lcd_Print_String(string2display);
    }
    
    drumchannel = drumChannelMenu.selector;   
}

//MIDI CHANNEL MENU
void Function_E(void) {
    
    which_screen = MIDI_CHANNEL_MENU;
    lcd_print_once = 0;    
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(midiChannelMenu.selector % midiChannelMenu.number) + midiChannelMenu.address]); //transpose menu
        }
        lcd_print_once = 1;
    }
    
    if(midiChannelMenu.selector == 0) {Function_E_1();} //set MAIN MIDI channel
    if(midiChannelMenu.selector == 1) {Function_E_2();} //set DRUM MIDI channel
}

//PROGRAM CHANGE MENU
void Function_F(void) {
    
    which_screen = PROGRAM_CHANGE_MENU;
    lcd_print_once = 0;
    
    programChangeMenu.selector = patch_number;
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row2();
            Lcd_Print_String("Program #: "); //transpose menu
        }
        lcd_print_once = 1;
        
        //lcd print program #
        int2string(programChangeMenu.selector);
        Lcd_Set_Cursor(2,13);
        Lcd_Print_String(string2display);
    }
 
    patch_number = programChangeMenu.selector;
    controlChange(channel, program_change, programChangeMenu.selector);
}

//save to EEPROM
void Function_G_1 (void){

    which_screen = SAVES_MENU;
    encoder_click = 0;
    lcd_print_once = 0;    
        
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String("Save #:");
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(savesMenu.selector % savesMenu.number) + savesMenu.address]); //modes menu
        }
        lcd_print_once = 1;
    }
 
    if(savesMenu.selector == 4){eepromExit();} //cancel out of save/load menu
    else {
        //call saveToEEPROM here
        eeprom_write(0,(savesMenu.selector + 1));
        saveToEEPROM(savesMenu.selector + 1);
        exitSave();
    }
    
    savesMenu.selector = 0;
}

 //load from EEPROM
void Function_G_2 (void){
    
    which_screen = SAVES_MENU;
    encoder_click = 0;
    lcd_print_once = 0;    
        
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String("Load #:");
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(savesMenu.selector % savesMenu.number) + savesMenu.address]); //modes menu
        }
        lcd_print_once = 1;
    }
 
    if(savesMenu.selector == 4){eepromExit();} //cancel out of save/load menu
    else {
        //call loadFromEEPROM here
        eeprom_write(0,(savesMenu.selector + 1));
        loadFromEEPROM(savesMenu.selector + 1);
        exitLoad();
    }
    
    savesMenu.selector = 0;
}

//restore defaults
void Function_G_3 (void){

    while(encoder_click == 0); //wait for encoder click
    
    eeprom_write(0,0x00);       //restore DEFAULT settings (write 0x00 at address 0x00 in EEPROM)
    
    clear_row1();
    Lcd_Print_String("Restore Setting!");   //exit function 
    clear_row2();
    Lcd_Print_String("Rebooting...");   //exit function
    __delay_ms(2500);            //hold on this screen for 1/2 second
    RESET();

} 

//EEPROM MENU
void Function_G(void) {
    
    which_screen = EEPROM_MENU;
    lcd_print_once = 0;    
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(eepromMenu.selector % eepromMenu.number) + eepromMenu.address]); //transpose menu
        }
        lcd_print_once = 1;
    }
    
    if(eepromMenu.selector == 0) {Function_G_1();} //save EEPROM
    if(eepromMenu.selector == 1) {Function_G_2();} //load EEPROM
    if(eepromMenu.selector == 2) {Function_G_3();} //restore defaults
    if(eepromMenu.selector == 3) {eepromExit();} //cancel out of save/load menu
    
}

