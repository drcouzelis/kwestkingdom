#ifndef MAP_HEADER
#define MAP_HEADER


#include <Foundation/Foundation.h>
#include "KwestKingdom.h"
#include "Screen.h"


@interface Map : NSObject {
  int map[COLS][ROWS];
  int cols;
  int rows;
}


- setX: (int) x andY: (int) y toValue: (int) value;
- (int) getValueAtX: (int) x andY: (int) y;


@end


#endif