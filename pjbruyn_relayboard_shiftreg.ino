/**
 * Relay board control software
 * using a 74HC595 shift-register chip
 *
 * (cc) 2012 Luis Rodil-Fernandez
 */
#include "ShiftRegLib.h"
#include "Config.h"

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

unsigned long tmark = 0;  // reference timestamp
unsigned long interval = MAX_TIMEOUT;  // milliseconds to wait

#define TIMECTL_MAXTICKS  4294967295L
#define TIMECTL_INIT      0
int timeout(unsigned long tinterval, unsigned long *treference){
  unsigned long timeCurrent;
  unsigned long timeElapsed;
  int result = false;
  
  timeCurrent = millis();
  if(timeCurrent < *treference) {  // rollover detected
    timeElapsed = (TIMECTL_MAXTICKS-*treference)+timeCurrent;  //elapsed=all the ticks to overflow + all the ticks since overflow
  }
  else {
    timeElapsed = timeCurrent - *treference;  
  }

  if(timeElapsed >= tinterval) {
    *treference = timeCurrent;
    result = true;
  }
  
  return(result);  
}

unsigned long xmap(unsigned long x, unsigned long in_min, unsigned long in_max, unsigned long out_min, unsigned long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


int arr2int(int *arr) {
  int i;
  int retval = 0;

  for(i = 0; i < 8; i++) {
    int val = arr[i];
    val = val << (7 - i);
    retval |= val;
  }
  return retval;
}

void setup() {
  // start Serial for debuging purposes	
  Serial.begin(9600);
  sr.configure(srpin_latch, srpin_clock, srpin_data);
  pot_init();
}

void pot_init() {
  pinMode(potpin_ain, INPUT);
}

int pot_read() {
  return analogRead(potpin_ain);
}

void loop() {

  for(int j = 0; j < TOTAL_STATES; j++) {
    int *vec = outStates[j];
    int r = arr2int(vec);

    sr.latchDown();
      //count up on GREEN LEDs
      sr.writeByte(r); 
      //count down on RED LEDs
      //sr.writeByte(255-j);
    sr.latchUp();

    delay(interval);
    
    //count up routine
    int currentReading = pot_read();
    if( currentReading != potval ) {
      potval = currentReading;
      interval = xmap(potval, 0, 1024, 0, MAX_TIMEOUT); 
      Serial.print("interval = ");
      Serial.print(interval);
      Serial.print("ms.\n");
    } // if
  }

} // loop


