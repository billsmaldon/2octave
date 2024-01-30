2 OCTAVE MIDI CONTROLLER FIRMWARE

PIC18F4680 FIRMWARE v1.0 FOR PCB v1.0

PIC18F4680 FIRMWARE v2.0 FOR PCB v2.0

*NEW* MIDI Arpeggiator update for all PCB versions

PIC18F4680 FIRMWARE v1.0a FOR PCB v1.0

PIC18F4680 FIRMWARE v2.0a FOR PCB v2.0 & v2.1

*** NEW 2024 FIRMWARE VERSION ***

PIC18F4680 FIRMWARE v1.1a FOR PCB v1.0

PIC18F4680 FIRMWARE v2.1a FOR PCB v2.0 & v2.1

*** TEENSY FIRMWARE ***

TEENSY LC FIRMWARE FOR PCB v2.0 & v2.1

What's new v1.1a/v2.1a (2024)?

1) Turn cc while arpeggio ON

While an arpeggio is playing, turning a continuous controller 
caused stuck Note On messages. This has been fixed.

2) Un-block the code

When in the menu, pressing a key or turning a continuous 
controller was "blocked", meaning that the keyboard or 
potentiometers do nothing until the menu item currently being 
selected was set by clicking the encoder. Now, anywhere in the 
menu selection key presses and potentiometer turns will work.

3) Change keyboard mode while a key is held

If a key is held and the KEYBOARD MODE is changed, it waits for 
the key release and then changes the KEYBOARD MODE.

4) Digit brightness

Now the 7 segment digital display has a consistent brightness 
and is updated at 100 Hz. The only exception is when ARPEGGIO 
is ON.  There is some display flicker while an arpeggio is 
playing due to the increased CPU load on the microcontroller. 
Releasing the arpeggio eliminates any flicker in the display.

5) Noisy potentiometers

Potentiometers sometimes sent random control changes when no
continuous controller was being turned. This has been fixed.

What's new v1.0a/v2.0a (2023)?

1. Firmware can be compiled for any PCB version
2. 7 segment display flicker fixed
3. Potentiometer latency can be adjusted
4. Rotary encoder polarity
5. Pentatonic Major and Pentatonic Minor scales
6. Quick transpose
7. MIDI Arpeggiator

Copyright © 2023 Bill Smaldon

Licensed under the GNU GPL Version 3.

email: billsmaldon@gmail.com

The code of encoder.c and encoder.h is a derivative work of the code from

Buxtronix, which is licensed GPL v3. This code therefore is also licensed

under the terms of the GNU Public License, verison 3.

https://github.com/buxtronix/arduino/tree/master/libraries/Rotary
 
 
Note: new versions of MPLAB X and the XC8 compiler do not work!

Please use the following ide, compiler and the necessary peripheral library

MPLAB X v4.05

XC8 v1.45

PIC18F Legacy Peripheral Libraries v2.0

After installing all of these, you will have to link the peripheral library.

1) right click the project name
2) select "Properties"
3) under "XC8 global options", select "XC8 linker"
4) scroll down and check "Link in Peripheral Library"
5) the program should compile now

For full instructions on compiling or flashing the PIC, see:

How to flash the PIC.txt

How to compile the source.txt

How to compile for board version.txt
