#ifndef UTILITIES_HEADER
#define UTILITIES_HEADER

#ifdef __cplusplus
    extern "C" {
#endif 


typedef enum
{
  OFF = 0,
  ON
} FLAG;


typedef enum {
  UP,
  DOWN,
  LEFT,
  RIGHT
} DIRECTION;


/**
 * Generate a random number between low and high, inclusively.
 * The lower bound is "low".
 * The upper bound is "high".
 */
int random_number(int low, int high);


#ifdef __cplusplus
    }
#endif 

#endif
