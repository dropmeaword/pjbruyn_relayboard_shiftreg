#include "ShiftRegLib.h"

ShiftRegLib::ShiftRegLib() {
}

void ShiftRegLib::configure(int l, int c, int d) {
  _latch = l;
  _clock = c;
  _data = d;
  
  pinMode(_latch, OUTPUT);
  pinMode(_data, OUTPUT);  
  pinMode(_clock, OUTPUT);
}

void ShiftRegLib::latchDown() {
  //ground latchPin and hold low for as long as you are transmitting
  digitalWrite(_latch, 0);
}

void ShiftRegLib::latchUp() {
  //return the latch pin high to signal chip that it 
  //no longer needs to listen for information
  digitalWrite(_latch, 1);
}


void ShiftRegLib::writeByte(byte dataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(_clock, OUTPUT);
  pinMode(_data, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(_data, 0);
  digitalWrite(_clock, 0);

  //for each bit in the byte myDataOut
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i = 7; i >= 0; i--)  {
    digitalWrite(_clock, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( dataOut & (1<<i) ) {
      pinState = 1;
    }
    else {	
      pinState = 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(_data, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(_clock, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(_data, 0);
  }

  //stop shifting
  digitalWrite(_clock, 0);
}

void ShiftRegLib::writeState(int out, int state) {
  // the bits you want to send
  byte bitsToSend = 0;

  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(_latch, LOW);

  // turn on the next highest bit in bitsToSend:
  bitWrite(bitsToSend, out, state);

  // shift the bits out:
  shiftOut(_data, _clock, MSBFIRST, bitsToSend);

    // turn on the output so the LEDs can light up:
  digitalWrite(_latch, HIGH);
}

