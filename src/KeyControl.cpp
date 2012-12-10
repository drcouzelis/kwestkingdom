#include <allegro.h>

#include "KeyControl.h"


KeyControl::KeyControl(int aKey) {
  keyCode = aKey;
  released = true;
  timer = 0;
  delay = 0; //GAME_TICKER / 4;
}


bool KeyControl::isPressed() {
  
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


void KeyControl::setDelay(bool theDelay) {
  delay = theDelay;

}




