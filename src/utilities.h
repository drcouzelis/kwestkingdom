#ifndef UTILITIES_H
#define UTILITIES_H


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


int random_number(int low, int high);


#endif

