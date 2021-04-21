2 OCTAVE MIDI CONTROLLER FIRMWARE

PIC18F4680 FIRMWARE v1.0

FOR PCB v1.0

Copyright 2021 Bill Smaldon

Licensed under the GNU GPL Version 3.

email: billsmaldon@gmail.com

The code of encoder.c and encoder.h is a derivative work of the code from

Buxtronix, hich is licensed GPL v3. This code therefore is also licensed

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
