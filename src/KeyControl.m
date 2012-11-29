#import "KeyControl.h"


@implementation KeyControl


- initWithKey: (int) aKey {
  self = [super init];
  if (self) {
    keyCode = aKey;
    released = YES;
    timer = 0;
    delay = 0; //GAME_TICKER / 4;
  }
  return self;
}


- (BOOL) isPressed {
  
  BOOL ret = NO;
  
  if (delay == 0 && key[keyCode]) {
    return YES;
  }
  
  if (key[keyCode]) {
    if (released) {
      
      ret = YES;
      timer = 0;
      
    } else {
      timer++;
    }
    
    released = NO;
    
    if (timer >= delay) {
      released = YES;
    }
    
  } else {
    released = YES;
  }
  
  return ret;
  
}


- setDelay: (BOOL) theDelay {
  delay = theDelay;
  return self;
}


@end

