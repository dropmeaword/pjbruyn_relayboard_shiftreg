#ifndef SHIFTREG_LIB_H
#define SHIFTREG_LIB_H

#include <arduino.h>
#include <inttypes.h>

class ShiftRegLib {

public:
  ShiftRegLib();
  void configure(int l, int c, int d);

  void writeByte(byte dataOut);
  void writeState(int out, int state);

  void latchDown();
  void latchUp();
  
private:
  // pin spec
  int _latch;
  int _clock;
  int _data;
};

#endif

