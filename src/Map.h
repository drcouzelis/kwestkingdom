#import <Foundation/Foundation.h>
#import "KwestKingdom.h"
#import "Screen.h"


@interface Map : NSObject {
  int map[COLS][ROWS];
  int cols;
  int rows;
}


- setX: (int) x andY: (int) y toValue: (int) value;
- (int) getValueAtX: (int) x andY: (int) y;


@end
