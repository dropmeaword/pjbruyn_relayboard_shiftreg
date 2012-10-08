/**
 * Relay board control software
 * using a 74HC595 shift-register chip
 *
 * (cc) 2012 Luis Rodil-Fernandez
 */
#include "ShiftRegLib.h"

// pin connected to ST_CP of 74HC595
int srpin_latch = 8;
// pin connected to SH_CP of 74HC595
int srpin_clock = 12;
// pin connected to DS of 74HC595
int srpin_data = 11;

ShiftRegLib sr;


void setup() {
  // start Serial for debuging purposes	
  Serial.begin(9600);
  sr.configure(srpin_latch, srpin_clock, srpin_data);
}

void loop() {
  //count up routine
  for (int j = 0; j < 256; j++) {
    sr.latchDown();
      //count up on GREEN LEDs
      sr.writeByte(j); 
      //count down on RED LEDs
      //sr.writeByte(255-j);
    sr.latchUp();
    
    delay(1000);
  }
}

