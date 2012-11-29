#import <Foundation/Foundation.h>
#import <allegro.h>
#import "KwestKingdom.h"


@interface KeyControl : NSObject {
  int keyCode;
  BOOL released;
  int timer; // Update every tick while the key is pressed
  int delay; // Number of ticks to wait until the action for this key is performed again
}


- initWithKey: (int) aKey;
- setDelay: (BOOL) theDelay;
- (BOOL) isPressed;


@end

