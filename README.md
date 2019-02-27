# Arduino Monoflop
Intended to be used to handle timing sensitive operation of the C2 protocol. Tested with Arduino Mega, but should work with Arduino Uno. The sketch contains different port manipulation definitions automatically selected at build time.

## Input
* Trigger (DIO 11): active-low. Intended to be connected to c2strb on the Rpi.
* Length (DIO 12): HIGH= strobe, LOW= reset. Intended to be connected to c2clk on the Rpi.

## Output
* Output (DIO 13): intended to be connected directed to the C2 line on the Silicon labs MCU.
