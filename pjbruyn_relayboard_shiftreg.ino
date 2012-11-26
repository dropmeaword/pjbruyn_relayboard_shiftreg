/**
 * Relay board control software
 * using a 74HC595 shift-register chip
 *
 * (cc) 2012 Luis Rodil-Fernandez
 */
#include "ShiftRegLib.h"

// pin connected to ST_CP of 74HC595
int srpin_latch = 10;
// pin connected to SH_CP of 74HC595
int srpin_clock = 9;
// pin connected to DS of 74HC595
int srpin_data = 12;

// analog input pin for pontentiometer
int potpin_ain = 3;
int potval = 0;

ShiftRegLib sr;


void setup() {
  // start Serial for debuging purposes	
  Serial.begin(9600);
  sr.configure(srpin_latch, srpin_clock, srpin_data);
}

void pot_init() {
  pinMode(potpin_ain, INPUT);
}

int pot_read() {
  return analogRead(potpin_ain);
}

void loop() {
  for (int j = 0; j < 256; j++) {
    sr.latchDown();
      //count up on GREEN LEDs
      sr.writeByte(j); 
      //count down on RED LEDs
      //sr.writeByte(255-j);
    sr.latchUp();
    
    delay(100);
    
    //count up routine
    int currentReading = pot_read();
    if( currentReading != potval ) {
      potval = currentReading;
      Serial.println(potval);
    } // if
  } // for
  
} // loop

