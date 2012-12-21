#include <allegro.h>
#include <stdio.h>

#include "key_input.h"


KEY_INPUT *create_key_control(int key, int delay)
{
  keyCode = key;
  delay = delay;
  released = ON;
  timer = 0;
}


FLAG is_key_pressed(KEY_INPUT *input)
{
  FLAF ret = OFF;
  
  if (delay == 0 && key[keyCode]) {
    return ON;
  }
  
  if (key[keyCode]) {
    if (released) {
      
      ret = ON;
      timer = 0;
      
    } else {
      timer++;
    }
    
    released = OFF;
    
    if (timer >= delay) {
      released = ON;
    }
    
  } else {
    released = ON;
  }
  
  return ret;
}

