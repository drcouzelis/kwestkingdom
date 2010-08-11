#ifndef UTILITIES_HEADER
#define UTILITIES_HEADER


#include <allegro.h>


typedef enum
{
  OFF = 0,
  ON
} FLAG;


/**
 * Generate a random number between low and high.
 */
int random_number(int low, int high);


#endif
