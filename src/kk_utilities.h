#ifndef KK_UTILITIES_H
#define KK_UTILITIES_H


#include <allegro.h>


typedef enum FLAG FLAG;
typedef enum DIRECTION DIRECTION;


enum FLAG
{
  OFF = 0,
  ON  = 1
};


enum DIRECTION {
  UP,
  DOWN,
  LEFT,
  RIGHT
};


int KK_random_number(int low, int high);


#endif

