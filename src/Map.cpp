#include "Map.h"





Map::Map() {
  
  int x;
  int y;
  
  cols = COLS;
  rows = ROWS;
  for (x = 0; x < COLS - 1; x++) {
    for (y = 0; y < ROWS - 1; y++) {
      map[x][y] = 0;
    }
  }
}


void Map::set(int x, int y, int value) {
  if (x >= 0 && x <= cols - 1 && y >= 0 && y <= rows - 1) {
    map[x][y] = value;
  }

}


int Map::getValue(int x, int y) {
  if (x >= 0 && x <= cols - 1 && y >= 0 && y <= rows - 1) {
    return map[x][y];
  }
  return 0;
}



