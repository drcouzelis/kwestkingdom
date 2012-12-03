#ifndef MAP_HEADER
#define MAP_HEADER


#include "KwestKingdom.h"
#include "Screen.h"


class Map {
  int map[COLS][ROWS];
  int cols;
  int rows;
public:

  Map();

  void set(int x, int y, int value);
  int getValue(int x, int y);
};


#endif
