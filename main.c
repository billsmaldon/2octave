/* 2 OCTAVE MIDI CONTROLLER FIRMWARE 
 * 
 *  PIC18F4680 FIRMWARE v1.0
 *  FOR PCB v1.0
 * 
 * Copyright 2021 Bill Smaldon
 * Licensed under the GNU GPL Version 3.
 * email: billsmaldon@gmail.com
 * 
 * Note: new versions of MPLAB X and the XC8 compiler do not work!
 * 
 * Please use the following ide, compiler and the necessary peripheral library
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
 /****************************************************************
*   MIDI_TRANSMIT
*	based on MIDI_RECEIVE
******************************************************************
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
*   4 digit 7 segment display
*   16x2 LCD
* 
*   WHICH PORTS FOR I/O?
* 
*   PORTA
*   - using external analog MUX to use 1 pin of PORTA ADC
*   RA0 is ADC analog input - connected to 74HC4067 MUX pin 1
*   RA1, RA2, RA3, RA4 are the selector bits of 74HC4067 MUX IC
*   RA5 unused
* 
*	PORTB
*   - has interrupts on input pin change
*   RB0 - encoder click
*   RB1 - !LOAD of 74HC165
*   RB2 - unused
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
*   RE3 unused
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
#include <stdint.h>
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

#define _XTAL_FREQ 20000000

//number of digital inputs, number of analog inputs
#define NUM_DIGITAL 40  //set to 40 (for PCB)
//#define NUM_ANALOG 16  //set to 16 (for PCB) (also in potentiometers.h)

//SOFTWARE DEBOUNCE DELAYS(for pushbutton input)
#define switch_debounce_ms 10
#define encoder_click_debounce_ms 10

//PIC setup function
void setup (void) {
    
    //setup port directions
    TRISA = 0b000001;           //RA0 is ADC analog input - connected to 74HC4067 MUX pin 1
                                //RA1, RA2, RA3, RA4 are the selector bits of 74HC4067 MUX IC
                                //RA5 unused

    TRISB = 0b00110001;         //RB0 - encoder click
                                //RB1 - !LOAD of 74HC165
                                //RB2 - unused
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
                                //RE3 unused
    
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
    
    //timer interrupt (unused)
    //T08BIT = 0; //timer is 16 bit
    //T0CS = 0; //timer is in counter mode
    //T0CON &= 0b11111000;
    //T0CON |= 0b00000010;   //set prescaler to ??? 1:256
    //PSA = 0;    //assign prescaler
    //TMR0ON = 1; //timer 0 on
    //TMR0IE = 1; //timer 0 interrupt enable
    
    PEIE = 1;   //enable peripheral interrupts
    GIE = 1;    //global interrupt enable

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
}

//shift/!load
void load(void){
    RB1 = 0; //LOAD
    __delay_ms(switch_debounce_ms);
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
    //button_state_now = button_state_now & 0x000FFFFF; //extra bitmask here
}

//read potentiometers - will need to test with NUM_ANALOG = 16 (PCB)
void analogInputs(void) {
    readPotentiometers();
}

//read input switches - will need to modify this code to 40 bits of input (PCB)
void digitalInputs(void){

    buttonInputsSerial();   // get all 32 bits of input "now"
    
    //when there is a mismatch of "now" and "last", processInputs
    if(button_state_now != button_state_last) {
        processKeyboard();
        //processDrumpad();
        processOctave();
        button_state_last = button_state_now;   //set last = now
    }
    
    //when there is a mismatch of "now" and "last", process drum inputs
    if(drum_button_state_now != drum_button_state_last) {
        processDrumpad();
        drum_button_state_last = drum_button_state_now;   //set last = now
    }    
}

//interrupt service routine
void interrupt ISR (void) {

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
    
    //call display on interrupt (unused)
    //if(TMR0IF==1) {
    //    display();
    //    TMR0IF = 0;
    //} 
}

//this function transmits an "ALL NOTES OFF" on channel and drumchannel
void panic_button(void){
    controlChange (channel, all_notes_off, 0x00);
    controlChange (drumchannel, all_notes_off, 0x00);
    //send a program change on reset
    //controlChange(channel, program_change, patch_number);
}

void initializeControllerNumbers(void){
    for (unsigned char i=0;i<16;i++){
        setControllerNumbers(i);
    }
}


int main(void) {
    
    //setup functions
    setup();
    ADC_Initialize();       //initialize ADC
    initializeMenuArray();  //initalize menu
    Lcd_Start();            //start LCD
    //initializeControllerNumbers();
    
    //various mode settings on start up
    state = R_START;            //start rotary encoder state machine
    DISPLAY_MODE = STRING;      //set 7 segment display mode to STRING
    POT_MODE = LO_RES;          //potentiometers default to 7 bit mode
    which_screen = MAIN_MENU;   //start LCD menu on "MAIN_MENU"   

    //eeprom slot settings (on boot-up)
    initializeSaveSlotsOnce();  //set Slot1 = Slot2 = Slot3 = Slot4 *once* (after programming)
    selectSlotOnBoot();         //select save slot to load on boot-up
    
    panic_button();             //transmit an "all notes off" on reset (channel/drumchannel)
    
    //infinite loop
    while(1) {

        digitalInputs();            //read digital inputs
        analogInputs();             //read analog inputs
        processEncoderBuxton();     //rotary encoder pins are read in ISR, processed here
        menu_lcd();                 //LCD menu
        display();                  //refresh the 7 segment display

    }
    
    return 0;
}

