#import <objc/Object.h>
#import "KwestKingdom.h"
#import "Screen.h"


@interface Map : Object {
  int map[COLS][ROWS];
  int cols;
  int rows;
}


- setX: (int) x andY: (int) y toValue: (int) value;
- (int) getValueAtX: (int) x andY: (int) y;


@end
