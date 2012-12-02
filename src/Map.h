#ifndef MAP_HEADER
#define MAP_HEADER


#include <Foundation/Foundation.h>
#include "KwestKingdom.h"
#include "Screen.h"


class Map : public NSObject {
  int map[COLS][ROWS];
  int cols;
  int rows;
public:


  setX: (int) x andY: (int) y toValue: (int) value;
  (int) getValueAtX: (int) x andY: (int) y;


};


#endif