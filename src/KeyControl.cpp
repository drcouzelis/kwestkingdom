#include "KeyControl.h"


@implementation KeyControl


- initWithKey: (int) aKey {
  self = [super init];
  if (self) {
    keyCode = aKey;
    released = true;
    timer = 0;
    delay = 0; //GAME_TICKER / 4;
  }
  return self;
}


- (bool) isPressed {
  
  bool ret = false;
  
  if (delay == 0 && key[keyCode]) {
    return true;
  }
  
  if (key[keyCode]) {
    if (released) {
      
      ret = true;
      timer = 0;
      
    } else {
      timer++;
    }
    
    released = false;
    
    if (timer >= delay) {
      released = true;
    }
    
  } else {
    released = true;
  }
  
  return ret;
  
}


- setDelay: (bool) theDelay {
  delay = theDelay;
  return self;
}


@end

