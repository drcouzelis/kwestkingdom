#import "Map.h"


@implementation Map


- init {
  
  int x;
  int y;
  
  self = [super init];
  if (self) {
    cols = COLS;
    rows = ROWS;
    for (x = 0; x < COLS - 1; x++) {
      for (y = 0; y < ROWS - 1; y++) {
        map[x][y] = 0;
      }
    }
  }
  
  return self;
  
}


- setX: (int) x andY: (int) y toValue: (int) value {
  if (x >= 0 && x <= cols - 1 && y >= 0 && y <= rows - 1) {
    map[x][y] = value;
  }
  return self;
}


- (int) getValueAtX: (int) x andY: (int) y {
  if (x >= 0 && x <= cols - 1 && y >= 0 && y <= rows - 1) {
    return map[x][y];
  }
  return 0;
}


@end
