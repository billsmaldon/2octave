/* 2 OCTAVE MIDI CONTROLLER FIRMWARE 
* 
*  PIC18F4680 FIRMWARE v1.1a/v2.1a (MIDI Arpeggiator update)
* 
*  FOR PCB v1.0
*  FOR PCB v2.0, v2.1 (with change to a #define in 'main.h')
* 
* Copyright 2024 Bill Smaldon
* Licensed under the GNU GPL Version 3.
* email: billsmaldon@gmail.com
* 
* FIXES: (from version 1.0a/2.0a)
* 
* 1) Turn cc while arpeggio ON
*
* While an arpeggio is playing, turning a continuous controller 
* caused stuck Note On messages. This has been fixed.
*
* 2) Un-block the code
*
* When in the menu, pressing a key or turning a continuous 
* controller was "blocked", meaning that the keyboard or 
* potentiometers do nothing until the menu item currently being 
* selected was set by clicking the encoder. Now, anywhere in the 
* menu selection key presses and potentiometer turns will work.
*
* 3) Change keyboard mode while a key is held
*
* If a key is held and the KEYBOARD MODE is changed, it waits for 
* the key release and then changes the KEYBOARD MODE.
*
* 4) Digit brightness
*
* Now the 7 segment digital display has a consistent brightness 
* and is updated at 100 Hz. The only exception is when ARPEGGIO 
* is ON.  There is some display flicker while an arpeggio is 
* playing due to the increased CPU load on the microcontroller. 
* Releasing the arpeggio eliminates any flicker in the display.  
*
* 5) Noisy potentiometers
*
* Potentiometers sometimes sent random control changes when no 
* continuous controller was being turned. This has been fixed.
*
********************************************************************************
*
* Note: new versions of MPLAB X and the XC8 compiler do not work!
* 
* Please use the following ide, compiler and the necessary  peripheral library
* 
* MPLAB X v4.05
* XC8 v1.45
* PIC18F Legacy Peripheral Libraries v2.0
* 
* After installing all of these, you will have to link the peripheral library.
*
* 1) right click the project name
* 2) select "Properties"
* 3) under "XC8 global options", select "XC8 linker"
* 4) scroll down and check "Link in Peripheral Library"
* 5) the program should compile now
* 
* Note: MPLAB must be set to use 32 bit floats!
* (add instructions here)
*
/****************************************************************
*   MIDI_TRANSMIT
*	based on MIDI_RECEIVE
*****************************************************************
* 
*	Midi transmit at 31.250 kbps, 8-bits x 3, using the USART.
*
*   INPUTS:
*   2 octave pushbutton keyboard
*   octave up/down buttons
*   1x modifier button
*   8x rhythym buttons
*   1x rotary encoders
*   7x potentiometers
*   7x fader potentiometer
*   2 axis analog joystick for pitch bend and modulation
*    
*	OUTPUTS:
*   MIDI out (5 pin DIN connector)
*   USB MIDI out (micro USB)
*   4 digit 7 segment display
*   16x2 LCD
* 
*   WHICH PORTS FOR I/O?
* 
*   PORTA
*   - using external analog MUX to use 1 pin of PORTA ADC
*
*   RA0 is ADC analog input - connected to 74HC4067 MUX pin 1
*   RA1, RA2, RA3, RA4 are the selector bits of 74HC4067 MUX IC
*   RA5  Teensy LC - clockPin
* 
*	PORTB
*   - has interrupts on input pin change
*
*   RB0 - encoder click
*   RB1 - !LOAD of 74HC165
*   RB2 - Teensy LC - messageReady
*   RB3 - PGM
*   RB4, RB5 - encoder A, B
*   RB6 - PGC
*   RB7 - PGD
* 
*   PORTC
*   RC0-RC3 (lower nibble) is digit select (7 seg)
*   RC4 is serial input (74HC165)
*   RC5 is CLK output (74HC165)
*   RC6 is MIDI output (USART)
*   RC7 is USART RX input (unused)
* 
*   PORTD
*   entire port - 7 segment outputs
*   also RD4, RD5, RD6, RD7 are the DATA bits of the LCD (in 4 bit mode)
* 
*	PORTE
*   RE0 is RS of LCD
*   RE1 is EN of LCD
*   RE2 Teensy LC - dataPin
*
****************************************************************/

// PIC18F4680 Configuration Bit Settings
// 'C' source line config statements

// CONFIG1H
#pragma config OSC = HS         // Oscillator Selection bits (HS oscillator)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (VBOR set to 2.1V)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config BBSIZ = 1024     // Boot Block Size Select bits (1K words (2K bytes) Boot Block)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (00C000-00FFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (00C000-00FFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "lcd.h"
#include "theory.h"
#include "adc.h"
#include "midi.h"
#include "encoder.h"
#include "keyboard.h"
#include "ascii.h"
#include "drum.h"
#include "octave.h"
#include "segment.h"
#include "potentiometers.h"
#include "menu.h"
#include "eeprom.h"
#include "arpeggio.h"

//PIC setup function
void setup (void) {
    
    //setup port directions
    TRISA = 0b000001;           //RA0 is ADC analog input - connected to 74HC4067 MUX pin 1
                                //RA1, RA2, RA3, RA4 are the selector bits of 74HC4067 MUX IC
                                //RA5 - Teensy LC - clockPin

    TRISB = 0b00110001;         //RB0 - encoder click
                                //RB1 - !LOAD of 74HC165
                                //RB2 - Teensy LC - messageReady
                                //RB3 - PGM
                                //RB4, RB5 - encoder A, B
                                //RB6 - PGC
                                //RB7 - PGD
    
    TRISC = 0b10010000;         //RC0-RC3 (lower nibble) is digit select (7 seg)
                                //RC4 is serial input (74HC165)
                                //RC5 is CLK output (74HC165)
                                //RC6 is MIDI output (USART)
                                //RC7 is USART RX input (unused)
                              
    TRISD = 0b00000000;         //entire port - segment outputs
                                //also RD4, RD5, RD6, RD7 are the DATA bits of the LCD (in 4 bit mode)
    
    TRISE = 0b000;              //RE0 is RS of LCD
                                //RE1 is EN of LCD
                                //RE3 Teensy LC - dataPin
    
    //clear all ports
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;

    //configure interrupts
    IPEN = 0; //Disable priority levels on interrupts (PIC16CXXX Compatibility mode)

    //PORTB interrupt stuff
    RBIF = 0;   //RB Port Change Interrupt Flag bit
    RBIE = 1;   //RB Port Change Interrupt Enable bit (RB4-RB7)
    
    INTEDG0 = 0;    //interrupt on falling edge (RB0)
    INT0IF = 0;     //INT0 External Interrupt Flag bit
    INT0IE = 1;     //interrupt on edge (RB0) INT0 External Interrupt Enable bit
    
    //TIMER0 interrupt (generates PPQN for arpeggiator)
    T08BIT = 0; //timer is 16 bit
    T0CS = 0;   //timer is in counter mode
    T0CON &= 0b11111000;
    T0CON |= 0b00000001;   //set prescaler to 4
    PSA = 0;    //assign prescaler
    TMR0ON = 0; //timer 0 on
    TMR0IE = 1; //timer 0 interrupt enable
    
    //TIMER2 interrupt (timing for 7 segment display, potentiometer fine/coarse) 
    T2CON = 0b01000001; //PRESCALE 1:4, POSTSCALE 1:9
    TMR2 = 0x83;        //timer 2 PRELOAD
    TMR2ON = 0;         //timer 2 on
    TMR2IE = 0;         //timer 2 interrupt enable
    
    //TIMER1 interrupt (for potentiometers coarse/fine)
    T1CON = 0b10000000;
    TMR1 = 0xEC78;
    TMR1ON = 0;
    TMR1IE = 1;
    
    //initialize UART
    //TXSTA
    TXEN = 1;               //Transmit Enable bit
    SYNC = 0;               //UART asynchronous mode
    
    //RCSTA
    SPEN = 1;               //Enables Serial Port
    CREN = 1;               //Enables Continuous Reception
    
    //BRG
    BRGH = 0;               //Baud rate generator LOW
    SPBRG = 9;              //Writing SPBRG Register for 31.250 Kbps (20 MHz!!!)
    
    PEIE = 1;   //enable peripheral interrupts
    GIE = 1;    //global interrupt enable      
}

//shift/!load
void load(void){
    RB1 = 0; //LOAD
    //__delay_ms(switch_debounce_ms);   //commented out!
    RB1 = 1; //SHIFT
}

//clock
void clock(void){
    RC5 = 1; //CLOCK HIGH
    RC5 = 0; //CLOCK LOW
}

//data in
void buttonInputsSerial(void) {
    
    button_state_now = 0; //clear
    drum_button_state_now = 0; //clear
    load(); //latch pushbuttons
    
    //shift in drum buttons to a char
    for (unsigned char i = 0;i<12;i++){
        drum_button_state_now = (drum_button_state_now << 1) | (RC4);
        clock();
    }
    
    //shift in the rest of the buttons (keyboard + octave + shift)
    for (unsigned char i = 0;i<28;i++){
        button_state_now = (button_state_now << 1) | (RC4); //shift in the pushbuttons
        clock();
    }
}

//read potentiometers
void analogInputs(void) {
    
    // might need to set this to a range, to allow time for controlChange() to finish
 
    // !!!KEEP THIS!!!
    //if((TIMER_OVERFLOWS > 0) && (TIMER_OVERFLOWS < 6)) {
    
    // !!! MODIFY TO THIS !!!
    
    // !!! LEFT OFF HERE !!!
    
    // turn CC (over DIN connector) while arpeggio playing FIXED!
    // next: make programChange() transmit only 1 byte!
    // next: digit brightness is not equal while ARPEGGIO is ON and press encoder "click" (while in menu)
    
    // read potentiometers asynchronously (if arpeggiator OFF)
    if(ARPEGGIO_ON == 0) {
        readPotentiometers();
    }
    
    // read potentiometers synchronously (if arpeggiator ON)
    if(ARPEGGIO_ON == 1) {
        //if((TIMER_OVERFLOWS > 0) && (TIMER_OVERFLOWS < (NOTE_LENGTH_PULSES / 2))) {
        //MODIFY TO THIS!
        if((TIMER_OVERFLOWS > 0) && (TIMER_OVERFLOWS < (NOTE_LENGTH_PULSES - 2))) {
            readPotentiometers();
        }
    }
    
}

//read input switches
void digitalInputs(void){

    buttonInputsSerial();   // get all 40 bits of input "now"
    
    //when there is a mismatch of "now" and "last", process inputs
    if(button_state_now != button_state_last) {
        processOctave();
        keyboardTranspose();
        processKeyboard();
        button_state_last = button_state_now;   //set last = now
    }
    
    //when there is a mismatch of "now" and "last", process drum inputs
    if(drum_button_state_now != drum_button_state_last) {
        processOctave();
        processDrumpad();
        drum_button_state_last = drum_button_state_now;   //set last = now
    }
}

//interrupt service routine
void interrupt ISR (void) {

    //TIMER INTERRUPT - FOR 7 SEGMENT DISPLAY
    if(TMR2IF==1){
        display();      //7 segment display
        //count_ISR++;    //counter incremented in ISR
        TMR2 = 0x83;    //TIMER2 preload
        TMR2IF = 0;     //TIMER2 interrupt flag
    }

    //TIMER INTERRUPT - FOR POTENTIOMETER COARSE/FINE
    if(TMR1IF==1){
        count_ISR++;    //counter incremented in ISR
        TMR1 = 0xEC78;    //TIMER1 preload
        TMR1IF = 0;     //TIMER1 interrupt flag
    }    
    
    //check for RB0 edge detect interrupt (falling edge)
    if(INT0IF==1) {
        __delay_ms(encoder_click_debounce_ms);  //wait for encoder click debounce delay
        if(RB0 == 0){encoder_click = 1;}        //if button is still pressed, set encoder click
        INT0IF = 0;                             //clear interrupt flag
    }

    //check for PortB change interrupt
    if(RBIF==1) { 
        encoderInputsBuxton();                  //read encoder bits
        //processEncoderBuxton();               //process encoder bits
        RBIF = 0;                               //clear interrupt flag
    }

    
    //TIMER INTERRUPT - FOR ARPEGGIATOR
    if(TMR0IF==1) {

        TMR0IE = 0; //TIMER0 interrupt enable

        //if TIMER_OVERFLOWS = NOTE_LENTH_PULSES and not finishLastNote
        if((finishLastNote == 0) && ((TIMER_OVERFLOWS % NOTE_LENGTH_PULSES) == 0)){

            //save octave
            if((ARPEGGIO_TYPE == AS_PRESSED) || (ARPEGGIO_TYPE == UP) || (ARPEGGIO_TYPE == DOWN) || (ARPEGGIO_TYPE == UP_DOWN) || (ARPEGGIO_TYPE == DOWN_UP)){
                stored_octave = which_octave;
            }

            // !!! COMMENTED ALL OF THESE OUT !!!
            //if(KEYBOARD_MODE == CHROMATIC){flag1 = 1; flag2 = 1;}
            //if(ARPEGGIO_TYPE == AS_PRESSED){flag1 = 0; flag2 = 0;}
            //if((ARPEGGIO_TYPE == UP) || (ARPEGGIO_TYPE == DOWN)){flag1 = 0; flag2 = 0;}
            //if(ARPEGGIO_TYPE == DOWN_UP){flag1 = 0; flag2 = 0;}
            //if(ARPEGGIO_TYPE == UP_DOWN){flag1 = 1; flag2 = 1;}

            
            // !!! display number of notes pressed in arpeggio
            // !!! display number of notes remaining in arpeggio
            // !!! display current step number
            //printThisNumber(MAX_NUM_NOTES - NUM_NOTES_PRESSED)
            //if(ARPEGGIO_ON == 1){
            //    if(DISPLAY_STEP_NUMBER == 1) {printThisNumber((NUM_NOTES_PRESSED * 100) + (which_note + 1));} //display step number
            //}
            
            //RC
                    
            //here set/clear USART_IS_BUSY!
            ARPEGGIO_IS_PLAYING = 1; //put this at top of function!
            playArpeggio();
            ARPEGGIO_IS_PLAYING = 0; //put this at end of function!

            // !!! clear all of these bits after playArpeggio() !!!
            suppress_note_on = 0;
            suppress_note_off = 0;
            flag1 = 0;
            flag2 = 0;
            
            //save octave for RANDOM, RANDOM_NON_REPEATING
            if((ARPEGGIO_TYPE == RANDOM) || (ARPEGGIO_TYPE == RANDOM_NON_REPEATING)) {
                stored_octave = which_octave;
            }
        }

        /*
        if(lastNoteMode == immediate){
            if(finishLastNote == 1){
                
                //comment out!
                //TMR0ON = 0; //stop TIMER0

                // !!! COMMENTED OUT !!!
                //suppress_note_on = 1; //suppress next noteOn()
                //playArpeggio();
                
                finishLastNote = 0; //returns to regular playArpeggio() mode
                
                // !!! COMMENTED OUT !!!
                TIMER_OVERFLOWS = NOTE_LENGTH_PULSES; //make next noteOn() immediate (after key release)
            }
        }
        */
        
        if(lastNoteMode == finishLast){
            if((finishLastNote == 1) && ((TIMER_OVERFLOWS % NOTE_LENGTH_PULSES) == 0)){
                
                //comment out!
                //TMR0ON = 0; //stop TIMER0
   
                // !!! COMMENTED OUT !!!
                //suppress_note_on = 1; //suppress next noteOn()
                //playArpeggio();
                
                finishLastNote = 0; //returns to regular playArpeggio() mode
                
                // !!! COMMENTED OUT !!!
                TIMER_OVERFLOWS = NOTE_LENGTH_PULSES; //make next noteOn() immediate (after key release)
            }
        }

        TIMER_OVERFLOWS++; //count up every timer overflow
        //reset every NOTE_LENGTH_PULSES
        if(TIMER_OVERFLOWS >= (NOTE_LENGTH_PULSES)){TIMER_OVERFLOWS = 0;}
        
        TMR0 = TIMER_PRELOAD;   //TIMER0 PRELOAD
        TMR0IF = 0;             //timer 0 interrupt flag
        TMR0IE = 1;             //timer 0 interrupt enable
    }
}

//this function transmits an "ALL NOTES OFF" on channel and drumchannel
void panic_button(void){
    controlChange (channel, all_notes_off, 0x00);
    controlChange (drumchannel, all_notes_off, 0x00);
    //send a program change on reset
    //programChange(channel, patch_number, patch_number);
}

//controller numbers for all the potentiometers
void initializeControllerNumbers(void){
    for (unsigned char i=0;i<16;i++){
        setControllerNumbers(i);
    }
}


int main(void) {

    //setup functions
    setup();                //PIC setup
    ADC_Initialize();       //initialize ADC
    initializeMenuArray();  //initalize menu
    Lcd_Start();            //start LCD

    //various settings on start up
    state = R_START;            //start rotary encoder state machine
    POT_MODE = LO_RES;          //potentiometers default to 7 bit mode
    which_screen = MAIN_MENU;   //start LCD menu on "MAIN_MENU"   
    menu_lcd();                 //update LCD before testing 7 segment
    panic_button();             //transmit an "all notes off" on reset (channel/drumchannel)

    srand(2048);                //random number seed

    //read encoder polarity from EEPROM
    encoderPolarity = eeprom_read(0x02);
    //read potentiometer alpha from EEPROM
    ema_integer = eeprom_read(0x03);
    //calculate potentiometer alpha, from an int to a float (divide by 100.0)
    calculate_alpha();
    
    // COMMENTED THIS OUT! ---> is in the .h !!!
    //coarse/fine ISR
    //number_of_interrupts = (int) coarse_fine_delay_ms / 2.5; //in TIMER2 interrupts (2.5 mS)
    
    //arpeggio ON/OFF
    ARPEGGIO_ON = 0;
    
    //calculate note length (once) --- re-calculate whenever changing BPM!
    TIMER_PRELOAD = calculate_pulse_length();
    
    //arpeggio LATCH settings
    LATCH = 0;              //hold arpeggio if keys released
    UN_LATCH_MODE = ALL;    //un-latch notes 'ALL' or 'ONE_AT_A_TIME'
                            //ONE_AT_A_TIME has bugs, will need to fix!
    AUTO_LATCH = 0;         //automatically add notes to the arpeggio

    //how random arpeggios are randomized
    AUTO_RANDOMIZE = AUTOMATICALLY;         //re-randomize at the end of every arpeggio
    //AUTO_RANDOMIZE = ONCE_PER_PRESS;      //re-randomize with button press

    //reset on key press, reset on key release
    RESET_ON_KEY_PRESS = 1;                 //can't get *not reset* to work, leave out of menu!
    RESET_ON_KEY_RELEASE = 1;    
    
    //last note mode for various button presses
    LAST_NOTE_MODE_KEY_PRESS = immediate;   //last note mode KEY PRESS
    LAST_NOTE_MODE_KEY_RELEASE = immediate; //last note mode KEY RELEASE
    LAST_NOTE_MODE_TRANSPOSE = finishLast;    //last note mode TRANSPOSE
    LAST_NOTE_MODE_RESET = finishLast;        //last note mode RESET
    
    //skip first/last notes of UP_DOWN/DOWN_UP arpeggio
    skipFirstLast = 0;
    
    //print step number of playing arpeggio
    DISPLAY_STEP_NUMBER = 0;
    
    //TIMER INTERRUPTS
    TMR0IE = 1; //timer 0 interrupt enable
    TMR0ON = 1; //timer 0 off
    
    TMR2IE = 1; //timer 2 interrupt enable
    TMR2ON = 1; //timer 2 on
    
    TMR1IE = 1; //timer 1 interrupt enable
    TMR1ON = 1; //timer 1 on    
    
    //eeprom slot settings (on boot-up)
    initializeSaveSlotsOnce();  //set Slot1 = Slot2 = Slot3 = Slot4 *once* (after programming)
    selectSlotOnBoot();         //select save slot to load on boot-up
    
    //*must* set startingDirection if ARPEGGIO_TYPE set to DOWN or DOWN_UP arpeggio at compile time!
    if((ARPEGGIO_TYPE == UP) || (ARPEGGIO_TYPE == UP_DOWN) || (ARPEGGIO_TYPE == RANDOM) || (ARPEGGIO_TYPE == RANDOM_NON_REPEATING) || (ARPEGGIO_TYPE == AS_PRESSED)){
        startingDirection = UP;
    }
    
    if((ARPEGGIO_TYPE == DOWN) || (ARPEGGIO_TYPE == DOWN_UP)){
        startingDirection = DOWN;
    }        

    displayTest();  //test the 7 segment display
    
    // !!! LEFT OFF HERE !!!
    //lights digits of the 7 segment display each time playArpeggio() is called!
    
    //which inputs are read in while() loops:
    //which_functions_are_unblocked = encoder_only;
    which_functions_are_unblocked = buttons_and_potentiometers_too;
        
    //infinite loop
    while(1) {

        //PUT THESE 3 FUNCTIONS IN un_block_code()
        digitalInputs();            //read digital inputs
        analogInputs();             //read analog inputs
        processEncoderBuxton();     //rotary encoder pins are read in ISR, processed here
      
        //this function updates the buttons, potentiometers and the encoder
        //un_block_code();
        
        //update the LCD menu (lower nibble of PORTC is bit masked out)
        
        // can comment out TMR2ON and PORTC bitmask now!
        //TMR2ON = 0;                 //TIMER2 OFF
        //PORTD = 0;
        //PORTC &= 0xF0;              //not light up 7 segments while printing to LCD!
        menu_lcd();                 //LCD menu
        //TMR2ON = 1;                 //TIMER2 ON
    }
    
    return 0;
}

