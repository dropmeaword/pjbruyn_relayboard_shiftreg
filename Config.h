#ifndef __CONFIG_H__
#define __CONFIG_H__

/* increase the value of TOTAL_STATES to match the number of lines
 * in the outStates list
 * remember that each state in the list is composed of 8 values
 * when the value = 1 it means the relay is on (device plugged is on)
 * when the value = 0 it means the relay is off (device plugged is off)
 */
#define TOTAL_STATES 10
int outStates[TOTAL_STATES][8] = {
  {1, 1, 1, 1, 1, 1, 1, 1},  // 255
  {0, 1, 0, 1, 0, 1, 0, 1},  //  85
  {1, 0, 1, 0, 1, 0, 1, 0},  // 170
  {0, 0, 0, 0, 0, 0, 1, 1},  //   3
  {0, 0, 0, 0, 0, 1, 1, 0},  //   6
  {0, 0, 0, 0, 1, 1, 0, 0},  //  12
  {0, 0, 0, 1, 1, 0, 0, 0},  //  24
  {0, 0, 1, 1, 0, 0, 0, 0},  //  48
  {0, 1, 1, 0, 0, 0, 0, 0},  //  96
  {1, 1, 0, 0, 0, 0, 0, 0},  // 192
};

/* to define the maximum timeout keep the following in mind:
 * multiply the number of seconds by 1000
 * multiply the number of minutes by 60000 (or 60*1000)
 * so a delay of 3 seconds would be 3*1000
 * and a delay of 5 minutes would be 5*60*1000
 */
#define MAX_TIMEOUT 6*1000 // in milliseconds ==> (minutes*60*1000)

#endif // __CONFIG_H__
