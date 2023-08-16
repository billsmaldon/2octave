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
    encoderPolarityMenu = menuArray[18];
    arpeggiatorMenu = menuArray[19];
    arpeggiatorOnOffMenu = menuArray[20];
    arpeggiatorTypeMenu = menuArray[21];
    arpeggiatorNoteLengthMenu = menuArray[22];
    arpeggiatorLatchMenu = menuArray[23];
    arpeggiatorLatchOnOffMenu = menuArray[24];
    arpeggiatorAutoLatchOnOffMenu = menuArray[25];
    arpeggiatorUnLatchModeMenu = menuArray[26];
    arpeggiatorRandomizeSkipMenu = menuArray[27];
    arpeggiatorRandomizeTypeMenu = menuArray[28];
    arpeggiatorSkipFirstLastMenu = menuArray[29];
    arpeggiatorLastNoteModeMenu = menuArray[30];
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
void int2string(signed int number) { //changed from signed char to signed int
    
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
                Function_H();
                exitFunction();
                break;
            case 2:
                Function_B();
                exitFunction();
                break;
            case 3:
                Function_C();
                exitFunction();
                break;
            case 4:
                Function_D();
                exitFunction();
                break;
            case 5:
                Function_E();
                exitFunction();
                break;
            case 6:
                Function_F();
                exitFunction();
                break;
            case 7:
                Function_G();
                //exitFunction();
                break;
                
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
    
    modeMenu.selector = which_mode;
    
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
    
    triadMenu.selector = which_triad;
        
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
    
    seventhMenu.selector = which_seventh;
    
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
    
    keyboardMenu.selector = KEYBOARD_MODE;
    
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
    
    transposeMenu.selector = TRANSPOSE_MODE;
    
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
    
    drumCCTypeMenu.selector = CONTROL_MODE;
    
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
    
    drumMenu.selector = DRUM_MODE;
    
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

//set POTENTIOMETER ALPHA
void Function_D_2(void){

    which_screen = POTS_ALPHA_MENU;
    lcd_print_once = 0;
    encoder_click = 0;
    
    potsAlphaMenu.selector = ema_integer;
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        lcd_print_once = 1;
        //lcd print potentiometer alpha
        int2string(potsAlphaMenu.selector);
        Lcd_Set_Cursor(2,13);
        Lcd_Print_String(string2display);
    }
    
    ema_integer = potsAlphaMenu.selector;
    eeprom_write (0x03,ema_integer); //save potentiometer alpha to EEPROM
    calculate_alpha();

}

//set POTENTIOMETER CC NUMBER
void Function_D_3(void){

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
void Function_D_4(void){
    
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
void Function_D_5(void){
    
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
    if(potsMenu.selector == 4) {Function_D_5();}
    
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
    programChange(channel, programChangeMenu.selector, 0x00);
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
    __delay_ms(2500);            //hold on this screen for 2 1/2 second
    RESET();

}

void Function_G_4 (void){

    // MODIFY THIS FOR CW/CCW ENCODER!!!
    
    which_screen = ENCODER_POLARITY_MENU;
    lcd_print_once = 0;
    encoder_click = 0;
    
    encoderPolarityMenu.selector = encoderPolarity;
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String("Encoder Polarity"); //keyboard menu            
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(encoderPolarityMenu.selector % encoderPolarityMenu.number) + encoderPolarityMenu.address]); //transpose menu
        }
        lcd_print_once = 1;
    }

    //write encoder polarity to EEPROM
    encoderPolarity = encoderPolarityMenu.selector;
    eeprom_write(0x02,encoderPolarityMenu.selector);
    exitFunction();

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
    if(eepromMenu.selector == 3) {Function_G_4();} //encoder polarity
    if(eepromMenu.selector == 4) {eepromExit();} //cancel out of save/load menu
    
}

/* ARPEGGIO MENU */

void Function_H(void) {
    
    which_screen = ARPEGGIATOR_MENU;
    lcd_print_once = 0;    
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(arpeggiatorMenu.selector % arpeggiatorMenu.number) + arpeggiatorMenu.address]); //transpose menu
        }
        lcd_print_once = 1;
    }

    if(arpeggiatorMenu.selector == 0) {Function_H_1();} // arpeggio OFF/ON
    if(arpeggiatorMenu.selector == 1) {Function_H_2();} // tempo
    if(arpeggiatorMenu.selector == 2) {Function_H_3();} // octave range
    if(arpeggiatorMenu.selector == 3) {Function_H_4();} // arpeggio type
    if(arpeggiatorMenu.selector == 4) {Function_H_5();} // note length
    if(arpeggiatorMenu.selector == 5) {Function_H_6();} // latch
    if(arpeggiatorMenu.selector == 6) {Function_H_7();} // un-latch
    if(arpeggiatorMenu.selector == 7) {Function_H_8();} // randomize/skip
    if(arpeggiatorMenu.selector == 8) {Function_H_9();} // last note mode
    
}

// arpeggio OFF/ON
void Function_H_1 (void) {

    which_screen = ARPEGGIATOR_ON_OFF_MENU;
    lcd_print_once = 0;
    encoder_click = 0;
    
    arpeggiatorOnOffMenu.selector = ARPEGGIO_ON;
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            //clear_row1();
            //Lcd_Print_String("Arpeggio OFF/ON");
            //clear_row2();
            //Lcd_Print_String(LCD_STRINGS[(arpeggiatorOnOffMenu.selector % arpeggiatorOnOffMenu.number) + arpeggiatorOnOffMenu.address]); //transpose menu
            if(arpeggiatorOnOffMenu.selector == 0) {
                clear_row2();
                Lcd_Print_String("ARPEGGIATOR OFF");
                DISPLAY_MODE = STRING;
                strcpy(string_to_display, "AoFF");
            }
            if(arpeggiatorOnOffMenu.selector == 1) {
                clear_row2();
                Lcd_Print_String("ARPEGGIATOR ON");
                DISPLAY_MODE = STRING;
                strcpy(string_to_display, " ArP");
            }            
        }
        lcd_print_once = 1;
    }

    ARPEGGIO_ON = arpeggiatorOnOffMenu.selector;

}

// tempo
void Function_H_2 (void) {
    
    which_screen = ARPEGGIATOR_TEMPO_MENU;
    lcd_print_once = 0;
    encoder_click = 0;
    
    arpeggiatorTempoMenu.selector = BPM;
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row2();
            Lcd_Print_String("Tempo (BPM): ");
        }
        lcd_print_once = 1;
        
        //lcd print tempo
        int2string(arpeggiatorTempoMenu.selector);
        Lcd_Set_Cursor(2,13);
        Lcd_Print_String(string2display);
    }
 
    BPM = arpeggiatorTempoMenu.selector;
    TIMER_PRELOAD = calculate_pulse_length(); //calculate once here!
}

// octaves
void Function_H_3 (void) {
    
    which_screen = ARPEGGIATOR_OCTAVES_MENU;
    lcd_print_once = 0;
    encoder_click = 0;
    
    arpeggiatorOctavesMenu.selector = OCTAVES;
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row2();
            Lcd_Print_String("Octave Range:"); //transpose menu
        }
        lcd_print_once = 1;
        
        //lcd print octave
        int2string(arpeggiatorOctavesMenu.selector);
        Lcd_Set_Cursor(2,13);
        Lcd_Print_String(string2display);
    }
 
    OCTAVES = arpeggiatorOctavesMenu.selector;

}

// arpeggio type
void Function_H_4 (void) {

    which_screen = ARPEGGIATOR_ARPEGGIO_TYPE_MENU,
    lcd_print_once = 0;
    encoder_click = 0;
        
    arpeggiatorTypeMenu.selector = ARPEGGIO_TYPE;
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String("Select Arpeggio:");
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(arpeggiatorTypeMenu.selector % arpeggiatorTypeMenu.number) + arpeggiatorTypeMenu.address]); //arpeggio type menu
        }
        lcd_print_once = 1;
    }
    
    ARPEGGIO_TYPE = arpeggiatorTypeMenu.selector;
    
    //changed to logical OR
    if((ARPEGGIO_TYPE == AS_PRESSED) || (ARPEGGIO_TYPE == UP) || (ARPEGGIO_TYPE == UP_DOWN) || (ARPEGGIO_TYPE == RANDOM) || (ARPEGGIO_TYPE == RANDOM_NON_REPEATING)) {
        startingDirection = UP;
    }
    //changed to logical OR
    if((ARPEGGIO_TYPE == DOWN) || (ARPEGGIO_TYPE == DOWN_UP)) {
        startingDirection = DOWN;
    }
        
    setupArpeggio();    //setup arpeggio with new ARPEGGIO_TYPE

}

// arpeggio note length
void Function_H_5 (void) {

    which_screen = ARPEGGIATOR_NOTE_LENGTH_MENU,
    lcd_print_once = 0;
    encoder_click = 0;
    
    //get array index
    for(unsigned char i = 0; i < 12; i++) {
        if(NOTE_LENGTH_PULSES_ARRAY[i] == NOTE_LENGTH_PULSES) {
            //arpeggiatorNoteLengthMenu.selector = NOTE_LENGTH_PULSES_ARRAY[i];
            arpeggiatorNoteLengthMenu.selector = i;
        }
    }
    
    //arpeggiatorNoteLengthMenu.selector = NOTE_LENGTH_PULSES;
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String("Note Length:");
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(arpeggiatorNoteLengthMenu.selector % arpeggiatorNoteLengthMenu.number) + arpeggiatorNoteLengthMenu.address]); //arpeggio note length menu
        }
        lcd_print_once = 1;
    }
    
    //NOTE_LENGTH_PULSES = arpeggiatorNoteLengthMenu.selector;
    NOTE_LENGTH_PULSES = NOTE_LENGTH_PULSES_ARRAY[arpeggiatorNoteLengthMenu.selector];
}


// arpeggio latch ON/OFF
void Function_H_6_1(void){

    which_screen = ARPEGGIATOR_LATCH_ON_OFF_MENU;
    lcd_print_once = 0; 
    encoder_click = 0;
    
    arpeggiatorLatchOnOffMenu.selector = LATCH;
        
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();Lcd_Print_String("Latch ON/OFF");
            if(arpeggiatorLatchOnOffMenu.selector == 0) {
                clear_row2();
                Lcd_Print_String("Latch OFF");
            }
            if(arpeggiatorLatchOnOffMenu.selector == 1) {
                clear_row2();
                Lcd_Print_String("Latch ON");
            }
         }
        lcd_print_once = 1;
    }
    
    LATCH = arpeggiatorLatchOnOffMenu.selector;
    
    if(LATCH == 1){
        /*
        latch_was_pressed = 1; //added this!
        DISPLAY_MODE = STRING;
        strcpy(string_to_display, "HoLd");
        */
        
        doTheLatch();
    }

    if(LATCH == 0){
    
        //temporarily store UN_LATCH_MODE
        unsigned char temp = UN_LATCH_MODE;
        
        UN_LATCH_MODE = ALL;    // UN_LATCH_MODE always 'ALL'!
        doTheUnLatch();
        
        //restore UN_LATCH_MODE
        UN_LATCH_MODE = temp;
        
        /*
        //DISPLAY_MODE = STRING;
        //strcpy(string_to_display, " oFF");        
    
        //must call playThisNote() for un-latch!
        
        ON_OFF = 0; //for key release

        // COPY THIS BLOCK OF CODE OVER TO octave.c (more efficient!)
        if(NUM_NOTES_PRESSED > 0) {
        
            //CHROMATIC SCALE, TRIADS, SEVENTH CHORDS
            if ((KEYBOARD_MODE == CHROMATIC) || KEYBOARD_MODE == TRIAD || KEYBOARD_MODE == SEVENTH){
                //playThisNote(0);
                if((ARPEGGIO_TYPE == AS_PRESSED) || (ARPEGGIO_TYPE == RANDOM) || (ARPEGGIO_TYPE == RANDOM_NON_REPEATING)){
                    playThisNote(ARPEGGIO[0]);
                }
                if((ARPEGGIO_TYPE == UP) || (ARPEGGIO_TYPE == UP_DOWN)){                
                    playThisNote(ARPEGGIO_SORTED[0]);
                }
                if((ARPEGGIO_TYPE == DOWN) || (ARPEGGIO_TYPE == DOWN_UP)){
                    playThisNote(ARPEGGIO_SORTED[NUM_NOTES_PRESSED - 1]);
                }
            }
            
            //MAJOR SCALE, MINOR SCALE, MODES, DIATONIC TRIADS, DIATONIC 7TH CHORDS
            if ((KEYBOARD_MODE == MAJOR) || (KEYBOARD_MODE == MINOR) || (KEYBOARD_MODE == MODES) || (KEYBOARD_MODE == DIATONIC_TRIAD_MAJOR) || (KEYBOARD_MODE == DIATONIC_TRIAD_MINOR)|| (KEYBOARD_MODE == DIATONIC_7TH_MAJOR) || (KEYBOARD_MODE == DIATONIC_7TH_MINOR)) {
                playThisNote8(0,0);
            }
            //PENTATONIC_MAJOR, PENTATONIC_MINOR
            if ((KEYBOARD_MODE == PENTATONIC_MAJOR) || (KEYBOARD_MODE == PENTATONIC_MINOR)){
                playThisNotePentatonic(0,0);
            }         
            
        }
        
        //all notes off, reset array index
        NUM_NOTES_PRESSED = 0;
        ARRAY_INDEX = 0;
        DISPLAY_MODE = STRING;
        strcpy(string_to_display, " oFF");
        */
        
    }
}
void Function_H_6_2(void){

    which_screen = ARPEGGIATOR_AUTO_LATCH_ON_OFF_MENU;
    lcd_print_once = 0; 
    encoder_click = 0;
    
    arpeggiatorAutoLatchOnOffMenu.selector = AUTO_LATCH;
        
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();Lcd_Print_String("AutoLatch ON/OFF");
            if(arpeggiatorAutoLatchOnOffMenu.selector == 0) {
                clear_row2();Lcd_Print_String("Auto Latch OFF");
                DISPLAY_MODE = STRING;
                strcpy(string_to_display, " oFF");
            }
            if(arpeggiatorAutoLatchOnOffMenu.selector == 1) {
                clear_row2();Lcd_Print_String("Auto Latch ON");
                DISPLAY_MODE = STRING;
                strcpy(string_to_display, "Auto");
            }
         }
        lcd_print_once = 1;
    }
    
    AUTO_LATCH = arpeggiatorAutoLatchOnOffMenu.selector;

}

// arpeggio latch menu
void Function_H_6 (void) {

    which_screen = ARPEGGIATOR_LATCH_MENU;
    lcd_print_once = 0;
    encoder_click = 0;
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(arpeggiatorLatchMenu.selector % arpeggiatorLatchMenu.number) + arpeggiatorLatchMenu.address]); //transpose menu
        }
        lcd_print_once = 1;
    }

    //call 2 different functions based on .selector
    if(arpeggiatorLatchMenu.selector == 0) {Function_H_6_1();}
    if(arpeggiatorLatchMenu.selector == 1) {Function_H_6_2();}
}

// un-latch mode
void Function_H_7 (void) {

    which_screen = ARPEGGIATOR_UN_LATCH_MODE_MENU;
    lcd_print_once = 0;
    encoder_click = 0;
    
    arpeggiatorUnLatchModeMenu.selector = UN_LATCH_MODE;
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String("Un-latch Mode:");
            clear_row2();
            //Lcd_Print_String(LCD_STRINGS[(arpeggiatorUnLatchModeMenu.selector % arpeggiatorUnLatchModeMenu.number) + arpeggiatorUnLatchModeMenu.address]);
            if(arpeggiatorUnLatchModeMenu.selector == 0) {
                clear_row2();Lcd_Print_String("UNLATCH ALL");
                DISPLAY_MODE = STRING;
                strcpy(string_to_display, " ALL");
            }
            if(arpeggiatorUnLatchModeMenu.selector == 1) {
                clear_row2();Lcd_Print_String("ONE AT A TIME");
                DISPLAY_MODE = STRING;
                strcpy(string_to_display, " OnE");
            }
         }
        lcd_print_once = 1;
    }
    
    UN_LATCH_MODE = arpeggiatorUnLatchModeMenu.selector;
}

// randomize type (auto or once per press)
void Function_H_8_1 (void){

    which_screen = ARPEGGIATOR_RANDOMIZE_TYPE_MENU;
    lcd_print_once = 0;
    encoder_click = 0;
    
    arpeggiatorRandomizeTypeMenu.selector = AUTO_RANDOMIZE;
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String("Randomize Type:"); //keyboard menu            
            //clear_row2();
            //Lcd_Print_String(LCD_STRINGS[(arpeggiatorRandomizeTypeMenu.selector % arpeggiatorRandomizeTypeMenu.number) + arpeggiatorRandomizeTypeMenu.address]);
            if(arpeggiatorRandomizeTypeMenu.selector == 0) {clear_row2();Lcd_Print_String("RANDOMIZE AUTO");}
            if(arpeggiatorRandomizeTypeMenu.selector == 1) {clear_row2();Lcd_Print_String("RANDOMIZE ONCE");}            
         }
        lcd_print_once = 1;
    }
    
    AUTO_RANDOMIZE = arpeggiatorRandomizeTypeMenu.selector;

}

// arpeggio skip first last
void Function_H_8_2 (void){

    which_screen = ARPEGGIATOR_SKIP_FIRST_LAST_MENU;
    lcd_print_once = 0; 
    encoder_click = 0;
    
    arpeggiatorSkipFirstLastMenu.selector = skipFirstLast;
        
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            if(arpeggiatorSkipFirstLastMenu.selector == 0) {clear_row2();Lcd_Print_String("Skip F/L OFF");}
            if(arpeggiatorSkipFirstLastMenu.selector == 1) {clear_row2();Lcd_Print_String("Skip F/L ON");}
         }
        lcd_print_once = 1;
    }
    
    skipFirstLast = arpeggiatorSkipFirstLastMenu.selector;

}

// arpeggio randomize/skip
void Function_H_8 (void) {
    
    which_screen = ARPEGGIATOR_RANDOMIZE_SKIP_MENU;
    lcd_print_once = 0;
    encoder_click = 0;
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(arpeggiatorRandomizeSkipMenu.selector % arpeggiatorRandomizeSkipMenu.number) + arpeggiatorRandomizeSkipMenu.address]); //transpose menu
        }
        lcd_print_once = 1;
    }

    //call 2 different functions based on .selector
    if(arpeggiatorRandomizeSkipMenu.selector == 0) {Function_H_8_1();} //randomize
    if(arpeggiatorRandomizeSkipMenu.selector == 1) {Function_H_8_2();} //skip

}

//arpeggiator last note mode key press
void Function_H_9_1(void){

    which_screen = ARPEGGIATOR_LAST_NOTE_MODE_KEY_PRESS_MENU;
    lcd_print_once = 0; 
    encoder_click = 0;
    
    arpeggiatorLastNoteModeKeyPressMenu.selector = LAST_NOTE_MODE_KEY_PRESS;
        
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String(LCD_STRINGS[(arpeggiatorLastNoteModeMenu.selector % arpeggiatorLastNoteModeMenu.number) + arpeggiatorLastNoteModeMenu.address]);
            if(arpeggiatorLastNoteModeKeyPressMenu.selector == 0) {clear_row2();Lcd_Print_String("IMMEDIATE");}
            if(arpeggiatorLastNoteModeKeyPressMenu.selector == 1) {clear_row2();Lcd_Print_String("FINISH LAST");}
         }
        lcd_print_once = 1;
    }
    
    LAST_NOTE_MODE_KEY_PRESS = arpeggiatorLastNoteModeKeyPressMenu.selector;
}

//arpeggiator last note mode key release
void Function_H_9_2(void){
    
    which_screen = ARPEGGIATOR_LAST_NOTE_MODE_KEY_RELEASE_MENU;
    lcd_print_once = 0; 
    encoder_click = 0;
    
    arpeggiatorLastNoteModeKeyReleaseMenu.selector = LAST_NOTE_MODE_KEY_RELEASE;
        
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String(LCD_STRINGS[(arpeggiatorLastNoteModeMenu.selector % arpeggiatorLastNoteModeMenu.number) + arpeggiatorLastNoteModeMenu.address]);
            if(arpeggiatorLastNoteModeKeyReleaseMenu.selector == 0) {clear_row2();Lcd_Print_String("IMMEDIATE");}
            if(arpeggiatorLastNoteModeKeyReleaseMenu.selector == 1) {clear_row2();Lcd_Print_String("FINISH LAST");}
         }
        lcd_print_once = 1;
    }
    
    LAST_NOTE_MODE_KEY_RELEASE = arpeggiatorLastNoteModeKeyReleaseMenu.selector;

}
//arpeggiator last note mode transpose
void Function_H_9_3(void){

    which_screen = ARPEGGIATOR_LAST_NOTE_MODE_TRANSPOSE_MENU;
    lcd_print_once = 0; 
    encoder_click = 0;
    
    arpeggiatorLastNoteModeTransposeMenu.selector = LAST_NOTE_MODE_TRANSPOSE;
        
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String(LCD_STRINGS[(arpeggiatorLastNoteModeMenu.selector % arpeggiatorLastNoteModeMenu.number) + arpeggiatorLastNoteModeMenu.address]);
            if(arpeggiatorLastNoteModeTransposeMenu.selector == 0) {clear_row2();Lcd_Print_String("IMMEDIATE");}
            if(arpeggiatorLastNoteModeTransposeMenu.selector == 1) {clear_row2();Lcd_Print_String("FINISH LAST");}
         }
        lcd_print_once = 1;
    }
    
    LAST_NOTE_MODE_TRANSPOSE = arpeggiatorLastNoteModeTransposeMenu.selector;
}


//arpeggiator last note mode reset
void Function_H_9_4(void){

    which_screen = ARPEGGIATOR_LAST_NOTE_MODE_RESET_MENU;
    lcd_print_once = 0; 
    encoder_click = 0;
    
    arpeggiatorLastNoteModeResetMenu.selector = LAST_NOTE_MODE_RESET;
        
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String(LCD_STRINGS[(arpeggiatorLastNoteModeMenu.selector % arpeggiatorLastNoteModeMenu.number) + arpeggiatorLastNoteModeMenu.address]);
            if(arpeggiatorLastNoteModeResetMenu.selector == 0) {clear_row2();Lcd_Print_String("IMMEDIATE");}
            if(arpeggiatorLastNoteModeResetMenu.selector == 1) {clear_row2();Lcd_Print_String("FINISH LAST");}
         }
        lcd_print_once = 1;
    }
    
    LAST_NOTE_MODE_RESET = arpeggiatorLastNoteModeResetMenu.selector;

}


// arpeggio last note mode menu
void Function_H_9 (void) {

    which_screen = ARPEGGIATOR_LAST_NOTE_MODE_MENU,
    lcd_print_once = 0;
    encoder_click = 0;
    
    while(encoder_click == 0) {
        processEncoderBuxton();
        if (lcd_print_once == 0) {
            clear_row1();
            Lcd_Print_String("Last Note Mode:"); //keyboard menu
            clear_row2();
            Lcd_Print_String(LCD_STRINGS[(arpeggiatorLastNoteModeMenu.selector % arpeggiatorLastNoteModeMenu.number) + arpeggiatorLastNoteModeMenu.address]);
        }
        lcd_print_once = 1;
    }
    
    //call 4 different functions based on .selector
    if(arpeggiatorLastNoteModeMenu.selector == 0) {Function_H_9_1();}
    if(arpeggiatorLastNoteModeMenu.selector == 1) {Function_H_9_2();}
    if(arpeggiatorLastNoteModeMenu.selector == 2) {Function_H_9_3();}
    if(arpeggiatorLastNoteModeMenu.selector == 3) {Function_H_9_4();}    
}