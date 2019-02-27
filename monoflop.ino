
/*
Arduino Monoflop
Used as clock driver for c2 programmer.
TRIGGER(11) is active-low.
LENGHT(12) 1=clock strobe, 0=reset signal
OUTPUT(13) is pulled-up.
Should work for both Arduino Mega (tested) and Arduino Uno (not tested).
*/

//Arduino Mega
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
//11
#define TRIGGER_BIT bit(5)
#define TRIGGER_PORT PORTB
#define TRIGGER_DIR DDRB
#define TRINGGER_INPUT PINB

//12
#define LENGHT_BIT bit(6)
#define LENGTH_PORT PORTB
#define LENGHT_DIR DDRB
#define LENGHT_INPUT PINB

//13
#define OUTPUT_BIT bit(7)
#define OUTPUT_DIR DDRB
#define OUTPUT_PORT PORTB

//Arduino Uno
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)

//11
#define TRIGGER_BIT bit(3)
#define TRIGGER_PORT PORTB
#define TRIGGER_DIR DDRB
#define TRINGGER_INPUT PINB

//12
#define LENGHT_BIT bit(4)
#define LENGTH_PORT PORTB
#define LENGHT_DIR DDRB
#define LENGHT_INPUT PINB

//13
#define OUTPUT_BIT bit(5)
#define OUTPUT_DIR DDRB
#define OUTPUT_PORT PORTB

#endif

void setup() {

  //Out
  OUTPUT_DIR |= OUTPUT_BIT;
  //In
  TRIGGER_DIR &= ~(TRIGGER_BIT);
  LENGHT_DIR &= ~(LENGHT_BIT);

  //Drive HIGH
  OUTPUT_PORT |= OUTPUT_BIT;

  //Set up Pull-ups
  TRIGGER_PORT |= TRIGGER_BIT;
  LENGTH_PORT |= LENGHT_BIT;

}

void loop() {
  //Active-low trigger signal
  if (!(TRINGGER_INPUT & TRIGGER_BIT)) {
    //Drive Low
    OUTPUT_PORT &= ~OUTPUT_BIT;
    if(!(LENGHT_INPUT & LENGHT_BIT)){
      //reset signal
      //29.12 us
      delayMicroseconds(30);
    } else {
      //clock strobe
      //2.06us = 206ns
       delayMicroseconds(3);
    }
   //Drive HIGH
    OUTPUT_PORT |= OUTPUT_BIT;

    while(!(TRINGGER_INPUT & TRIGGER_BIT)){
        // Wait until trigger goes HIGH again
    }
  }
  else {
    OUTPUT_PORT |= OUTPUT_BIT;
  }
}